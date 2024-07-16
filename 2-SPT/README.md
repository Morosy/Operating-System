## 2-SPT.c

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
$ gcc 2-SPT.c -o 2-SPT
$ ./2-SPT process.csv
```

#### 3. 結果
```
----- process -----
name, arrival_time, processing_time
A, 0, 2
B, 1, 10
C, 3, 7
D, 5, 3
-------------------
name, arrival_time, processing_time
A, 0, 2
D, 5, 3
C, 3, 7
B, 1, 10
-- process start --
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
13 | process: D
14 | process: D
15 | process: D finish
16 | process: C
17 | process: C
18 | process: C
19 | process: C
20 | process: C
21 | process: C
22 | process: C finish
--- process end ---

task | arrival_time | finish_time | response_time |
---------------------------------------------------
   A |            0 |           2 |           2.0 |
   B |            1 |          12 |          11.0 |
   C |            3 |          22 |          19.0 |
   D |            5 |          15 |          10.0 |
average response time: 10.5
```

#### 4. 2-SPT_time.c
処理関数に
```
sleep(1)
```
を追加することで，時間経過を再現
