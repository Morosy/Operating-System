## 5-Round-Robin.c

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
$ gcc 5-Round-Robin.c -o 5-Round-Robin
$ ./5-Round-Robin process.csv
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
-- process start --
 1 | process: A
 2 | process: A finish
 3 | process: B
 4 | process: B
 5 | process: C
 6 | process: C
 7 | process: D
 8 | process: D
 9 | process: B
10 | process: B
11 | process: C
12 | process: C
13 | process: D finish
14 | process: B
15 | process: B
16 | process: C
17 | process: C
18 | process: B
19 | process: B
20 | process: C finish
21 | process: B
22 | process: B finish
--- process end ---

task | arrival_time | finish_time | response_time |
---------------------------------------------------
   A |            0 |           2 |           2.0 |
   B |            1 |          22 |          21.0 |
   C |            3 |          20 |          17.0 |
   D |            5 |          13 |           8.0 |
average response time: 12.0
```

#### 4. 5-Round-Robin_time.c
処理関数に
```
sleep(1)
```
を追加することで，時間経過を再現
