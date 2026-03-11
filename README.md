 # RISC-V Instruction Set Simulator

  ## 项目概述

  这是一个用C语言实现的RISC-V指令集模拟器，支持RV32I基础指令集的核心指令。该
  项目是为了深入理解RISC-V指令集架构和处理器工作原理而开发的教学级模拟器。

  ## 实现功能

  ### 支持的指令 (15条)

  #### 算术指令 (3条)
  - `ADD rd, rs1, rs2` - 寄存器加法
  - `SUB rd, rs1, rs2` - 寄存器减法
  - `ADDI rd, rs1, imm` - 立即数加法

  #### 逻辑指令 (6条)
  - `AND rd, rs1, rs2` - 按位与
  - `OR rd, rs1, rs2` - 按位或
  - `XOR rd, rs1, rs2` - 按位异或
  - `ANDI rd, rs1, imm` - 立即数按位与
  - `ORI rd, rs1, imm` - 立即数按位或
  - `XORI rd, rs1, imm` - 立即数按位异或

  #### 移位指令 (3条)
  - `SLL rd, rs1, rs2` - 逻辑左移
  - `SRL rd, rs1, rs2` - 逻辑右移
  - `SRA rd, rs1, rs2` - 算术右移

  #### 访存指令 (2条)
  - `LW rd, offset(rs1)` - 加载字
  - `SW rs2, offset(rs1)` - 存储字

  #### 分支指令 (2条)
  - `BEQ rs1, rs2, offset` - 相等分支
  - `BNE rs1, rs2, offset` - 不等分支
  - `BLT rs1, rs2, offset` - 小于分支
  - `BGE rs1, rs2, offset` - 大于等于分支

  #### 跳转指令 (2条)
  - `JAL rd, offset` - 跳转并链接
  - `JALR rd, rs1, offset` - 寄存器跳转并链接

  ## 项目结构

  c_learning/
  ├── README.md          # 项目说明文档
  ├── riscv.h           # 头文件：数据结构和函数声明
  ├── cpu.c             # CPU初始化和调试功能
  ├── decoder.c         # 指令解码模块
  ├── executor.c        # 指令执行模块
  ├── main.c            # 主程序和测试用例
  └── riscv_sim         # 编译后的可执行文件

  ### 核心模块说明

  - **riscv.h**: 定义CPU结构、内存结构、指令格式和函数接口
  - **cpu.c**: CPU和内存的初始化，寄存器状态打印等辅助功能
  - **decoder.c**: 将32位机器指令解码为对应的指令格式（R/I/S/B/J型）
  - **executor.c**: 执行具体指令操作，更新CPU状态
  - **main.c**: 包含各种测试用例，验证指令实现的正确性

  ## 编译与运行

  ### 编译
  ```bash
  cd ~/c_learning
  gcc -o riscv_sim main.c cpu.c decoder.c executor.c

  运行

  ./riscv_sim

  测试结果

  模拟器包含以下测试用例：

  1. 基础指令测试

  - 算术运算：ADDI, ANDI, ADD等
  - 移位操作：SLL（左移）
  - 访存操作：SW/LW（存储/加载）
  - 比较操作：SLTI（小于比较）

  2. 分支指令测试

  - BEQ：相等跳转测试
  - BLT：小于跳转测试
  - BNE：不等跳转测试

  3. 循环程序测试

  - 斐波那契数列：计算第9项，结果为55
  - 累加求和：计算1+2+...+10，结果为55

  4. 函数调用测试

  - 实现multiply(5, 3)函数，通过循环加法计算5×3
  - 验证JAL/JALR指令的函数调用和返回机制
  - 结果：15（正确）

  示例输出

  >>> Test: Function Call - multiply(5, 3)
  [EXEC] JAL x1, 4096
    -> Save return address: x1 = 0x1004
    -> Jump to: 0x2000
  [EXEC] ADD: x12 =x12 + x10 = 5
  [EXEC] ADD: x12 =x12 + x10 = 10
  [EXEC] ADD: x12 =x12 + x10 = 15
  [EXEC] JALR: x0 = 0x0 (return addr)
  PC= (x1:4100 + 0) & ~1 = 0x1004
  Result: multiply(5, 3) = 15
  Expected: 15
  Success: YES

  技术特性

  指令格式支持

  - R型：寄存器-寄存器操作
  - I型：立即数操作和加载指令
  - S型：存储指令
  - B型：分支指令
  - J型：跳转指令

  关键技术实现

  1. 立即数符号扩展：正确处理有符号立即数
  2. 地址对齐：JALR指令确保跳转地址对齐
  3. x0寄存器特殊处理：硬编码为0，写入无效
  4. 分支跳转：PC相对寻址实现
  5. 函数调用约定：使用x1作为返回地址寄存器

  调试功能

  - 详细的指令执行日志
  - 寄存器状态跟踪
  - 执行统计信息
  - 步骤化调试输出

  学习收获

  通过实现这个RISC-V模拟器，我深入理解了：
  - RISC-V指令集架构的设计原理
  - 指令解码和执行的具体过程
  - 函数调用机制和返回地址管理
  - 分支跳转的实现方式
  - 处理器数据通路的基本概念

  使用说明

  1. 编译项目后运行可执行文件
  2. 程序会自动执行所有测试用例
  3. 观察输出结果验证指令实现的正确性
  4. 所有寄存器的最终状态会在程序结束时显示

  开发环境

  - 语言: C语言
  - 编译器: GCC
  - 操作系统: Linux
  - 目标架构: RISC-V RV32I

  ---此项目用于学习RISC-V指令集架构和处理器原理
