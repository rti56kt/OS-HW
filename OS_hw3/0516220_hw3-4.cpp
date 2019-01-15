#include <list>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    int total_process;
    int arrival_time[total_process], burst_time[total_process], remain_time[total_process];
    int H_time_quantum = 0;
    int M_time_quantum = 0;

    if(argc == 1){
        cin >> total_process;
        for(int i = 0; i < total_process; i++){
            cin >> arrival_time[i];
        }
        for(int i = 0; i < total_process; i++){
            cin >> burst_time[i];
        }
    }else{
        ifstream fin(argv[1]);
        fin >> total_process;
        for(int i = 0; i < total_process; i++){
            fin >> arrival_time[i];
        }
        for(int i = 0; i < total_process; i++){
            fin >> burst_time[i];
            remain_time[i] = burst_time[i];
        }
        fin >> H_time_quantum >> M_time_quantum;
        fin.close();
    }

    int waiting_time[total_process], turnaround_time[total_process];
    list<int> H_queue, M_queue, L_queue;
    double avg_wait_time, avg_turn_time;
    int remain_process = total_process, time_cnt = 0;
    int who_is_busy = -1;
    char now_process = 'N';
    int H_time = H_time_quantum;
    int M_time = M_time_quantum;

    for(int i = 0; i < total_process; i++){
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    while(remain_process){
        if(H_queue.empty() == false){
            for(list<int>::iterator it = H_queue.begin(); it != H_queue.end(); it++){
                waiting_time[*it]++;
            }
        }
        if(M_queue.empty() == false){
            for(list<int>::iterator it = M_queue.begin(); it != M_queue.end(); it++){
                waiting_time[*it]++;
            }
        }
        if(L_queue.empty() == false){
            for(list<int>::iterator it = L_queue.begin(); it != L_queue.end(); it++){
                waiting_time[*it]++;
            }
        }
        for(int i = 0; i < total_process; i++){
            if(arrival_time[i] == time_cnt){
                H_queue.push_back(i);
            }
        }
        if(who_is_busy != -1){
            remain_time[who_is_busy]--;
            if(now_process == 'H') H_time--;
            if(now_process == 'M') M_time--;
            if(remain_time[who_is_busy] == 0){
                turnaround_time[who_is_busy] = waiting_time[who_is_busy] + burst_time[who_is_busy];
                who_is_busy = -1;
                remain_process--;
                if(now_process == 'H') H_time = H_time_quantum;
                if(now_process == 'M') M_time = M_time_quantum;
            }else{
                if(now_process == 'H'){
                    if(H_time == 0){
                        M_queue.push_back(who_is_busy);
                        if(H_queue.empty() == false){
                            who_is_busy = H_queue.front();
                            H_queue.pop_front();
                        }else{
                            who_is_busy = -1;
                        }
                        H_time = H_time_quantum;
                    }
                }else if(now_process == 'M'){
                    if(M_time == 0){
                        for(list<int>::iterator it = L_queue.begin(); ; it++){
                            if(remain_time[who_is_busy] < remain_time[*it]){
                                L_queue.insert(it, who_is_busy);
                                break;
                            }
                            if(it == L_queue.end()){
                                L_queue.push_back(who_is_busy);
                                break;
                            }
                        }
                        if(H_queue.empty() == false){
                            who_is_busy = H_queue.front();
                            H_queue.pop_front();
                            now_process = 'H';
                        }else{
                            if(M_queue.empty() == false){
                                who_is_busy = M_queue.front();
                                M_queue.pop_front();
                            }else{
                                who_is_busy = -1;
                            }
                        }
                        M_time = M_time_quantum;
                    }else{
                        if(H_queue.empty() == false){
                            M_queue.push_front(who_is_busy);
                            who_is_busy = H_queue.front();
                            H_queue.pop_front();
                            now_process = 'H';
                        }
                    }
                }else if(now_process == 'L'){
                    if(H_queue.empty() == false){
                        L_queue.push_front(who_is_busy);
                        who_is_busy = H_queue.front();
                        H_queue.pop_front();
                        now_process = 'H';
                    }else if(M_queue.empty() == false){
                        L_queue.push_front(who_is_busy);
                        who_is_busy = M_queue.front();
                        M_queue.pop_front();
                        now_process = 'M';
                    }
                }
            }
        }
        if(who_is_busy == -1){
            if(H_queue.empty() == false){
                who_is_busy = H_queue.front();
                H_queue.pop_front();
                now_process = 'H';
            }else if(M_queue.empty() == false){
                who_is_busy = M_queue.front();
                M_queue.pop_front();
                now_process = 'M';
            }else if(L_queue.empty() == false){
                who_is_busy = L_queue.front();
                L_queue.pop_front();
                now_process = 'L';
            }
        }
        time_cnt++;
    }

    ofstream fout("ans4.txt");
    for(int i = 0; i < total_process; i++){
        fout << waiting_time[i] << " " << turnaround_time[i] << endl;
        avg_wait_time += waiting_time[i];
        avg_turn_time += turnaround_time[i];
    }
    avg_wait_time = (int)(avg_wait_time * 100000 + 0.5) / (100000 * total_process * 1.0);
    avg_turn_time = (int)(avg_turn_time * 100000 + 0.5) / (100000 * total_process * 1.0);
    fout << avg_wait_time << endl;
    fout << avg_turn_time << endl;
    fout.close();

    return 0;
}