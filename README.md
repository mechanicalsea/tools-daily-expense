## 日常支出统计工具

根据以文本形式记录的账单文件，该工具通过提取账单中的数字信息统计日常支出。

### 文本账单计算

- 程序名称：MonlyExpense
- 输入：`example/bill.txt`
- 输出：`example/costperday.txt`
- 源代码：`MonlyExpense.cpp`
- 编译程序：MonlyExpense

### 使用方法

1. 使用 C++ 编译器对 `MonlyExpense.cpp` 进行编译，获得可执行文件 MonlyExpense；
2. 准备 `example/bill.txt` 文件，其格式为
    ```
    早餐3.5，中餐22
    早餐3.5，中餐20，晚餐9
    早餐3.5，中餐17，晚餐18
    ```
3. 运行程序 MonlyExpense，获得每日支出，其格式为
    ```
    25.500
    32.500
    38.500
    ```

### 编译信息

该程序使用 C++ 实现，在 MacOS 系统上通过 c++17 编译。
