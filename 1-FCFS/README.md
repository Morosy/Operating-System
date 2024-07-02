## 1-FTFS.c

#### 1. 入力
入力は以下の例題を使用
|プロセス|到着時刻|処理時間|
|---|---|---|
|A|0|2|
|B|1|10|
|C|3|7|
|D|5|3|

以下形式でのcsvファイルとして保存
```csv:process.csv
name, arrival_time, processing_time
A, 0, 2
B, 1, 10
C, 3, 7
D, 5, 3
```

#### 2. 実行
実行時に引数としてファイル名を指定
``` bash
$ gcc FCFS.c -o FCFS
$ ./FCFS process.csv
```

#### 3. 結果
```
-- processing start --
 1 | process: A
 2 | process: A finish
 3 | process: B
 4 | process: B
 5 | process: B
 6 | process: B
 7 | process: B
 8 | process: B
 9 | process: B
10 | process: B
11 | process: B
12 | process: B finish
13 | process: C
14 | process: C
15 | process: C
16 | process: C
17 | process: C
18 | process: C
19 | process: C finish
20 | process: D
21 | process: D
22 | process: D finish
-- Processing end --

task | arrival_time | finish_time | response_time |
---------------------------------------------------
   A |            0 |           2 |             2 |
   B |            1 |          12 |            11 |
   C |            3 |          19 |            16 |
   D |            5 |          22 |            17 |
average response time: 11
```

