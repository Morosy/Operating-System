/* (5) Round-Robin */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "scheduler.h"

#define TIME_SLICE 2


void skip_line(FILE *);
int return_Process_Number(char *);
SCHEDULER *read_Process(SCHEDULER *, char *, int);
void print_process_list(SCHEDULER *, int);

SCHEDULER *sort_By_Arrival_Time(SCHEDULER *, int);
void sort_Arrival(SCHEDULER *, int);
int compare_Arrival(const void *, const void *);

void print_process(SCHEDULER, int);
void print_null(int);

void round_Robin_Processing(SCHEDULER *, int, int);
void shift_Scheduler(SCHEDULER *, int);

void status_init(SCHEDULER *, int);

double calc_Response_Time(SCHEDULER *, int);

void print_Response_Time(SCHEDULER *, int);



int main(int argc, char *argv[])
{
    // read process
    int process_num = return_Process_Number(argv[1]);
    // printf("process_num: %d\n", process_num);
    SCHEDULER *process;
    process = (SCHEDULER *)malloc(sizeof(SCHEDULER) * process_num);
    process = read_Process(process, argv[1], process_num);
    status_init(process, process_num);
    // read done

    printf("----- process -----\n");
    print_process_list(process, process_num);
    printf("-------------------\n");
    // process scan done

    process = sort_By_Arrival_Time(process, process_num);
    status_init(process, process_num);
    // sort done

    printf("-- process start --\n");
    round_Robin_Processing(process, process_num, TIME_SLICE);
    printf("--- process end ---\n");
    // processing done

    sort_By_Arrival_Time(process, process_num);
    print_Response_Time(process, process_num);

    free(process);

    return 0;
}







void round_Robin_Processing(SCHEDULER *process, int process_num, int time_slice)
{
    int i = 0;
    int time = 0;
    int slice = 0;
    int flag = 0;
    while(1){
        // 到着次第 status = 1
        if((process[0].arrival_time <= time) && (process[0].status == 0)){
            process[0].status = 1;
        }

        // 先頭のプロセスを実行状態に
        if(process[0].status == 1){
            process[0].status = 2;
        }else{
            shift_Scheduler(process, process_num);
            continue;
        }

        // 実行
        if(process[0].status == 2){
            for(int i = time_slice; i != 0; i--){
                time++;
                process[0].remaining_time--;
                print_process(process[0], time);
                if(process[0].remaining_time == 0){
                    break;
                }
                if(i == 1){
                    process[0].status = 1;
                }
            }
        }

        // 残り時間が0になったらstatus = 3
        if(process[0].remaining_time == 0){
            process[0].status = 3;
            process[0].finish_time = time;
        }
        shift_Scheduler(process, process_num);

        // 終了判定
        flag = 0;
        for(int j = 0; j < process_num; j++){
            if(process[j].status == 3){
                flag++;
            }
        }
        if(flag == process_num){
            break;
        }
    }
}




void shift_Scheduler(SCHEDULER *process, int process_num)
{
    SCHEDULER temp = process[0];
    for(int i = 0; i < process_num - 1; i++) {
        process[i] = process[i + 1];
    }
    process[process_num - 1] = temp;
}






void skip_line(FILE *fp)
{
    char tmp[256];
    fgets(tmp, sizeof(tmp), fp);
}



int return_Process_Number(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("file open error\n");
        exit(1);
    }

    int LINES = 0;
    char line[256];
    skip_line(fp);
    while(fgets(line, sizeof(line), fp) != NULL) {
        LINES++;
    }
    fclose(fp);
    return LINES;
}



SCHEDULER *read_Process(SCHEDULER *process, char *filename, int process_num)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("file open error\n");
        exit(1);
    }
    skip_line(fp);
    for(int i = 0; i < process_num; i++) {
        if(fscanf(fp, "%9[^,], %d, %d\n", process[i].name, &process[i].arrival_time, &process[i].processing_time) != 3) {
            printf("Error reading line %d\n", i + 1);
            exit(1);
        }
        process[i].status = 0;
        process[i].remaining_time = process[i].processing_time;
    }
    fclose(fp);
    return process;
}



void print_process_list(SCHEDULER *process, int number)
{
    printf("name, arrival_time, processing_time\n");
    for(int i = 0; i < number; i++){
        printf("%s, %d, %d\n", process[i].name, process[i].arrival_time, process[i].processing_time);
    }
}




SCHEDULER *sort_By_Arrival_Time(SCHEDULER *process, int process_num)
{
    sort_Arrival(process, process_num);
    return process;
}



int compare_Arrival(const void *a, const void *b)
{
    SCHEDULER *processA = (SCHEDULER *)a;
    SCHEDULER *processB = (SCHEDULER *)b;
    return (processA->arrival_time - processB->arrival_time);
}

void sort_Arrival(SCHEDULER *processes, int process_num)
{
    qsort(processes, process_num, sizeof(SCHEDULER), compare_Arrival);
}




void print_process(SCHEDULER process, int time)
{
    if(process.remaining_time != 0){
        printf("%2d | process: %s\n", time, process.name);
    }else{
        printf("%2d | process: %s finish\n", time, process.name);
    }
}

void print_null(int time)
{
    printf("%2d | \n", time);
}


double calc_Response_Time(SCHEDULER *process, int process_num)
{
    double response_time = 0;
    for(int i = 0; i < process_num; i++){
        process[i].response_time = (double)process[i].finish_time - (double)process[i].arrival_time;
        response_time += process[i].response_time;
        process[i].response_time = round(process[i].response_time * 10) / 10;
    }
    response_time /= process_num;
    response_time = round(response_time * 10) / 10;
    return response_time;
}

void print_Response_Time(SCHEDULER *process, int process_num)
{
    double response_time = calc_Response_Time(process, process_num);
    printf("\ntask | arrival_time | finish_time | response_time |\n");
    printf("---------------------------------------------------\n");
    for(int i = 0; i < process_num; i++){
        printf("%4s | %12d | %11d | %13.1f |\n", process[i].name, process[i].arrival_time, process[i].finish_time, process[i].response_time);
    }
    printf("average response time: %.1f\n", response_time);
}



void status_init(SCHEDULER *process, int N)
{
    for(int i = 0; i < N; i++){
        process[i].status = 0;
    }
}
