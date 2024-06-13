/* (1) 到着順 スケジューリングアルゴリズム
    (FCFS, First Come First Service) */

/* 処理している感を出すためにsleep関数を使用 */

// todo: main関数内の処理を関数化

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "scheduler.h"

scheduler schedule[26];


/* ---------- 構造体を到着順にソート ---------- */

/* 仕様
    到着時間が早い順にソート
    到着時間が同じ場合は、名前順にソート
    sort_processes(schedule型の配列, プロセス数)
*/

// 比較関数
int compare(const void *a, const void *b)
{
    scheduler *processA = (scheduler *)a;
    scheduler *processB = (scheduler *)b;
    if(processA->arrival_time == processB->arrival_time){
        return processA->name - processB->name;  // arrival_timeが同じ場合は、nameでソート
    }else{
        return processA->arrival_time - processB->arrival_time;
    }
}

// ソート関数
void sort_processes(scheduler *processes, int N)
{
    qsort(processes, N, sizeof(scheduler), compare);
}
/* ---------- 構造体をソート ---------- */



/* ---------- 処理中のプロセスを出力 ---------- */

/* 仕様
    process.remainint_time = 1 の場合は、"finish"を出力
    それ以外の場合は、"process"を出力
    processが処理されていない場合は，時間のみ出力
*/

void print_process(scheduler *processes, int process_num, int time)
{
    // todo: 条件の修正
    if(processes[process_num].remaining_time != 1){
        printf("%2d | process: %s\n", time, processes[process_num].name);
    }else{
        printf("%2d | process: %s finish\n", time, processes[process_num].name);
    }
}

void print_null(int time)
{
    printf("%2d | \n", time);
}
/* ---------- 処理中のプロセスを出力 ---------- */



/* ---------- 応答速度を計算・出力 ----------*/

/* 仕様
    応答速度 = 終了時間 - 到着時間
    応答速度の平均を計算・出力
*/

void response_time(scheduler *processes, int process_num)
{
    printf("\ntask | arrival_time | finish_time | response_time |\n");
    printf("---------------------------------------------------\n");
    int average_response_time = 0;
    for(int i = 0; i < process_num; i++){
        schedule[i].response_time = processes[i].finish_time - processes[i].arrival_time;
        average_response_time += schedule[i].response_time;
        printf("   %s | %12d | %11d | %13d |\n", processes[i].name, processes[i].arrival_time, processes[i].finish_time, processes[i].response_time);
    }
    average_response_time /= process_num;
    printf("average response time: %d\n", average_response_time);
}
/* ---------- 応答速度を計算・出力 ----------*/



/* ---------- 1行分の読み飛ばし ---------- */
/* 仕様
    引数ポインタから1行分に適用
    ファイルの1行を読み飛ばす
*/
void skip_scan(FILE *fp)
{
    char tmp[256];
    fgets(tmp, sizeof(tmp), fp);
}
/* ---------- 1行分の読み飛ばし ---------- */








int main(int argc, char *argv[])
{
    // filenameを引数で指定
    char file_name[100];
    strcpy(file_name, argv[1]);
    FILE *fp;
    fp = fopen(file_name, "r");
    if(fp == NULL){
        printf("File open error\n");
        return -1;
    }

    int i = 0;
    // 1行目を読み飛ばす
    skip_scan(fp);
    while(fscanf(fp, "%c, %d, %d\n", &schedule[i].name, &schedule[i].arrival_time, &schedule[i].processing_time) != EOF){
        // ! Debug ----------
        // printf("name[%d]:%s | arrival_time[%d]: %d, processing_time[%d]: %d\n", i, schedule[i].name, i,  schedule[i].arrival_time, i, schedule[i].processing_time);
        // ! ----------
        schedule[i].status = 0;
        schedule[i].remaining_time = schedule[i].processing_time;
        i++;
    }
    const int processes_num = i; // プロセス数
    int remaining_process = i; // 残りのプロセス数
    // ! Debug ----------
    // プロセス数を出力
    // printf("%d\n", processes_num);
    // ! ----------
    fclose(fp);
    sort_processes(schedule, processes_num); // 到着順にソート


    /* ---------- 処理部分 ---------- */
    printf("-- processing start --\n");
    int time = 1;

    // sleep


    i = 0;
    while(1){
        if(time >= schedule[i].arrival_time && schedule[i].status == 0){
            schedule[i].status = 1;
        }
        if(schedule[i].arrival_time <= time && schedule[i].status == 1){
            schedule[i].status = 2;
            /*  処理中
                残りの処理時間が0になるまで処理を続ける
            */
            for(schedule[i].remaining_time; schedule[i].remaining_time > 0; schedule[i].remaining_time--){
                print_process(schedule, i, time);
                // todo: ramaining_timeの減少方法を変更
                // todo: remaining_time = 0 にしたい
                schedule[i].finish_time = time;
                // todo: 終了時間記録の方法を変更
                time++;
                sleep(1);
            }
            schedule[i].status = 3;
            remaining_process--;
        }else if(schedule[i].arrival_time > time){
            print_null(time);
            time++;
        }else{
            printf("error\n");
        }
        i++;
        if(remaining_process == 0){
            break;
        }
    }
    printf("-- Processing end --\n");
    response_time(schedule, processes_num);
    return 0;
}
