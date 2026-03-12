 1. 🧩 RISC-V指令编码格式详解

  基本概念

  RISC-V所有指令都是32位固定长度，但根据功能不同分为5种格式。每种格式的位域
  分布不同，但都有共同的opcode字段。

  R型指令 (Register-Register)

  31    25|24  20|19  15|14  12|11   7|6    0
  funct7  | rs2  | rs1  |funct3|  rd  |opcode
    7位   | 5位  | 5位  | 3位  | 5位  | 7位

  用途: 两个寄存器之间的运算
  示例: ADD x3, x1, x2 (x3 = x1 + x2)
  funct7=0000000, rs2=00010(x2), rs1=00001(x1),
  funct3=000, rd=00011(x3), opcode=0110011

  I型指令 (Immediate)

  31        20|19  15|14  12|11   7|6    0
     imm[11:0]| rs1  |funct3|  rd  |opcode
      12位    | 5位  | 3位  | 5位  | 7位

  用途: 立即数运算、加载指令
  示例: ADDI x1, x0, 100 (x1 = x0 + 100)
  imm=000001100100(100), rs1=00000(x0),
  funct3=000, rd=00001(x1), opcode=0010011

  关键点: 立即数需要符号扩展！
  // 12位立即数符号扩展到32位
  int32_t imm_raw = (inst >> 20) & 0xFFF;  // 提取12位
  if (imm_raw & 0x800) {  // 检查最高位(符号位)
      imm = imm_raw | 0xFFFFF000;  // 负数: 高20位填1
  } else {
      imm = imm_raw;  // 正数: 高20位本来就是0
  }

  S型指令 (Store)

  31    25|24  20|19  15|14  12|11   7|6    0
  imm[11:5]| rs2  | rs1  |funct3|imm[4:0]|opcode
    7位    | 5位  | 5位  | 3位  | 5位   | 7位

  用途: 存储指令
  示例: SW x2, 4(x1) (Memory[x1+4] = x2)
  特点: 立即数被分割成两部分！
  // 重组立即数
  int32_t imm_11_5 = (inst >> 25) & 0x7F;  // 高7位
  int32_t imm_4_0 = (inst >> 7) & 0x1F;    // 低5位
  int32_t imm_raw = (imm_11_5 << 5) | imm_4_0;  // 重组12位

  B型指令 (Branch)

  31|30   25|24  20|19  15|14  12|11    8|7|6    0
  imm[12]|imm[10:5]|rs2|rs1|funct3|imm[4:1]|imm[11]|opcode
   1位  |  6位   |5位|5位| 3位 |  4位   | 1位 | 7位

  用途: 条件分支
  特点: 立即数编码最复杂！位序是乱的！
  // 提取各个位段
  int32_t imm_12 = (inst >> 31) & 0x1;    // 最高位
  int32_t imm_11 = (inst >> 7) & 0x1;     // 第11位
  int32_t imm_10_5 = (inst >> 25) & 0x3F; // 第10-5位
  int32_t imm_4_1 = (inst >> 8) & 0xF;    // 第4-1位

  // 重组: [12|11|10:5|4:1|0]，最低位强制为0
  int32_t imm_raw = (imm_12 << 12) | (imm_11 << 11) |
                    (imm_10_5 << 5) | (imm_4_1 << 1);
  // 最低位是0，保证地址2字节对齐

  J型指令 (Jump)

  31|30      21|20|19    12|11   7|6    0
  imm[20]|imm[10:1]|imm[11]|imm[19:12]|rd|opcode
   1位   |  10位   | 1位  |   8位    |5位| 7位

  用途: 无条件跳转
  特点: 立即数位序也是乱的！
  // 重组: [20|19:12|11|10:1|0]
  int32_t imm_20 = (inst >> 31) & 0x1;
  int32_t imm_19_12 = (inst >> 12) & 0xFF;
  int32_t imm_11 = (inst >> 20) & 0x1;
  int32_t imm_10_1 = (inst >> 21) & 0x3FF;

  int32_t imm_raw = (imm_20 << 20) | (imm_19_12 << 12) |
                    (imm_11 << 11) | (imm_10_1 << 1);

  2. 🔄 PC更新的三种情况详解

  情况1: 顺序执行 (Sequential)

  pc_next = pc + 4;
  何时发生: 大部分指令(算术、逻辑、访存等)
  原因: RISC-V指令固定4字节长度
  示例:
  0x1000: ADD x1, x2, x3
  0x1004: SUB x4, x1, x2  ← 下一条指令

  情况2: 分支跳转 (Branch)

  if (condition_met) {
      pc_next = pc + sign_extend(imm);  // PC相对跳转
  } else {
      pc_next = pc + 4;  // 条件不满足，顺序执行
  }

  具体条件:
  // BEQ: 相等则跳转
  if (rs1_data == rs2_data) pc_next = pc + imm;

  // BNE: 不等则跳转
  if (rs1_data != rs2_data) pc_next = pc + imm;

  // BLT: 小于则跳转(有符号)
  if ((int32_t)rs1_data < (int32_t)rs2_data) pc_next = pc + imm;

  示例: 循环实现
  loop:                    # 地址 0x1000
      ADDI x1, x1, 1      # x1++
      ADDI x2, x2, -1     # x2--
      BNE x2, x0, loop    # if (x2 != 0) goto loop
      # imm = 0x1000 - 0x1008 = -8 (向后跳转)

  情况3: 无条件跳转 (Jump)

  // JAL: Jump and Link
  rd = pc + 4;              // 保存返回地址
  pc_next = pc + imm;       // 跳转

  // JALR: Jump and Link Register
  rd = pc + 4;              // 保存返回地址
  pc_next = (rs1 + imm) & ~1;  // 通过寄存器跳转，地址对齐

  函数调用示例:
  main:
      JAL x1, function     # 调用函数，返回地址存x1
      ADDI x2, x0, 5       # ← 函数返回后执行这里

  function:
      # 函数体
      JALR x0, x1, 0       # 返回: 跳转到x1地址，不保存返回地址

  3. 🏗️ 5个硬件模块作用详解

  模块1: 寄存器堆 (regfile.v)

  module regfile (
      input clk, rst,
      input [4:0] rs1, rs2, rd,    // 寄存器地址
      input [31:0] wd,             // 写数据
      input we,                    // 写使能
      output [31:0] rs1_data, rs2_data  // 读数据
  );

  作用: CPU的"工作台"，存储临时数据
  特点:
  - 32个寄存器，每个32位
  - 2读1写端口(支持同时读2个，写1个)
  - x0硬编码为0，写入无效
  - 同步写入，组合读取

  时序:
  时钟上升沿: 写入数据 (if we=1)
  任意时刻: 立即读出数据

  模块2: ALU (alu.v)

  module alu (
      input [31:0] a, b,           // 两个操作数
      input [3:0] alu_ctrl,        // 控制信号
      output [31:0] result,        // 运算结果
      output zero                  // 零标志
  );

  作用: CPU的"计算器"，执行所有运算
  支持的10种操作:
  ALU_ADD:  result = a + b;
  ALU_SUB:  result = a - b;
  ALU_AND:  result = a & b;
  ALU_OR:   result = a | b;
  ALU_XOR:  result = a ^ b;
  ALU_SLL:  result = a << b[4:0];  // 逻辑左移
  ALU_SRL:  result = a >> b[4:0];  // 逻辑右移
  ALU_SRA:  result = $signed(a) >>> b[4:0];  // 算术右移
  ALU_SLT:  result = ($signed(a) < $signed(b)) ? 1 : 0;
  ALU_SLTU: result = (a < b) ? 1 : 0;

  零标志: 用于分支判断
  assign zero = (result == 32'h0);

  模块3: 指令存储器 (imem.v)

  module imem (
      input [31:0] pc,         // 程序计数器
      output [31:0] inst       // 输出指令
  );

  作用: 存储程序指令
  地址映射:
  wire [9:0] inst_addr = pc[11:2];  // 字节地址→字地址
  assign inst = memory[inst_addr];

  为什么右移2位？
  - PC是字节地址: 0, 4, 8, 12, ...
  - 存储器是字索引: 0, 1, 2, 3, ...
  - 转换: 字节地址 ÷ 4 = 字地址

  模块4: 数据存储器 (dmem.v)

  module dmem (
      input clk,
      input [31:0] addr,           // 访问地址
      input [31:0] write_data,     // 写数据
      input mem_write, mem_read,   // 读写控制
      output [31:0] read_data      // 读数据
  );

  作用: 存储程序数据(变量、数组等)
  时序特点:
  // 同步写入
  always @(posedge clk) begin
      if (mem_write) memory[word_addr] <= write_data;
  end

  // 组合读取
  assign read_data = mem_read ? memory[word_addr] : 32'h0;

  模块5: 指令解码器 (decoder.v)

  module decoder (
      input [31:0] inst,              // 输入指令
      output [6:0] opcode,            // 指令字段
      output [4:0] rs1, rs2, rd,
      output [31:0] imm,
      output reg reg_write,           // 控制信号
      output reg mem_write, mem_read,
      output reg [3:0] alu_ctrl,
      output reg alu_src, mem_to_reg
  );

  作用: CPU的"大脑"，分析指令并生成控制信号
  工作流程:
  1. 提取指令字段(opcode, rs1, rs2, rd)
  2. 生成立即数(根据指令类型)
  3. 生成控制信号(决定其他模块如何工作)

  4. 🔄 数据通路完整流程详解

  完整的5阶段流程

  阶段1: 取指 (Instruction Fetch)

  PC → IMEM → 32位指令
  具体过程:
  1. PC提供指令地址
  2. IMEM根据地址输出对应指令
  3. 指令送给decoder

  阶段2: 解码 (Instruction Decode)

  指令 → decoder → 控制信号 + 操作数地址 + 立即数
  具体过程:
  1. decoder分析opcode，确定指令类型
  2. 提取rs1, rs2, rd字段
  3. 生成立即数(根据指令类型不同处理)
  4. 生成所有控制信号

  阶段3: 读寄存器 (Register Read)

  rs1,rs2地址 → regfile → rs1_data, rs2_data
  具体过程:
  1. 用rs1, rs2地址访问寄存器堆
  2. 同时读出两个操作数
  3. 数据送给ALU

  阶段4: 执行 (Execute)

  操作数 → ALU → 运算结果
  数据选择:
  assign alu_a = rs1_data;                    // ALU输入A
  assign alu_b = alu_src ? imm : rs2_data;    // ALU输入B
  // alu_src=1: 使用立即数 (I型指令)
  // alu_src=0: 使用寄存器 (R型指令)

  阶段5: 访存/写回 (Memory/Writeback)

  ALU结果 → DMEM → 读数据 → 写回寄存器

  数据路径分支:
  // 访存指令
  if (mem_write) DMEM[addr] = write_data;  // SW指令
  if (mem_read) read_data = DMEM[addr];    // LW指令

  // 写回数据选择
  assign write_data_reg = mem_to_reg ? read_data :    // LW指令
                         jump ? (pc + 4) :            // JAL指令
                         alu_result;                  // 其他指令

  PC更新逻辑 (并行执行)

  always @(*) begin
      if (jump) begin
          if (opcode == OP_JAL)
              pc_next = pc + imm;              // JAL
          else
              pc_next = (rs1_data + imm) & ~1; // JALR
      end else if (branch_taken) begin
          pc_next = pc + imm;                  // 分支成功
      end else begin
          pc_next = pc + 4;                    // 顺序执行
      end
  end

  关键控制信号作用

  reg_write:   是否写回寄存器
  mem_write:   是否写内存
  mem_read:    是否读内存
  alu_src:     ALU第二操作数选择(0=寄存器, 1=立即数)
  mem_to_reg:  写回数据选择(0=ALU结果, 1=内存数据)
  branch:      是否是分支指令
  jump:        是否是跳转指令

  这样，一个完整的指令执行周期就完成了！每个时钟周期执行一条指令，这就是单周
  期CPU的特点。
