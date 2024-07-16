#ifndef scheduler_H
#define scheduler_H


typedef struct{
    // ? 処理中は不変
    char name[10];
    int arrival_time; // 到着時間
    int processing_time; // 必要処理時間

    // ? 以下はプログラム内で随時変更される
    int remaining_time; // 残り処理時間
    int finish_time; // 終了時間
    double response_time; // 応答速度
    int status;
    /* status =
    0: not arrived
    1: arrival and ready
    2: running
    3: finished
    */
}SCHEDULER;


#endif // scheduler_H
