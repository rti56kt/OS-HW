#include <list>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    int total_process;
    int arrival_time[total_process], burst_time[total_process];

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
        }
        fin.close();
    }

    int waiting_time[total_process], turnaround_time[total_process];
    list<int> wait_queue;
    double avg_wait_time, avg_turn_time;
    int remain_process = total_process, time_cnt = 0;
    int who_is_busy = -1;

    for(int i = 0; i < total_process; i++){
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    while(remain_process){
        for(int i = 0; i < total_process; i++){
            if(arrival_time[i] == time_cnt){
                if(wait_queue.empty() == true){
                    wait_queue.push_back(i);
                }else{
                    for(list<int>::iterator it = wait_queue.begin(); ; it++){
                        if(burst_time[i] < burst_time[*it]){
                            wait_queue.insert(it, i);
                            break;
                        }
                        if(it == wait_queue.end()){
                            wait_queue.push_back(i);
                            break;
                        }
                    }
                }
            }
        }
        if(who_is_busy != -1){
            if(turnaround_time[who_is_busy] + arrival_time[who_is_busy] == time_cnt){
                who_is_busy = -1;
                remain_process--;
            }
        }
        if(who_is_busy == -1 && wait_queue.empty() == false){
            who_is_busy = wait_queue.front();
            waiting_time[who_is_busy] = time_cnt - arrival_time[who_is_busy];
            turnaround_time[who_is_busy] = waiting_time[who_is_busy] + burst_time[who_is_busy];
            wait_queue.pop_front();
        }
        time_cnt++;
    }

    ofstream fout("ans1.txt");
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