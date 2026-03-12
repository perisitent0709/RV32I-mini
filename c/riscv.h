 #ifndef RISCV_H
  #define RISCV_H
  // ↑ 头文件保护：防止重复包含

  #include <stdint.h>  // uint32_t, uint8_t等类型
  #include <stdio.h>   // printf函数
  #include <stdlib.h>  // malloc, free等

  // ========== 寄存器定义 ==========
  #define REG_NUM 32  // RISC-V有32个通用寄存器

  // CPU结构体：包含32个寄存器和PC
  typedef struct {
      uint32_t x[REG_NUM];  // x0-x31寄存器
      uint32_t pc;          // 程序计数器
  } CPU;

  // ========== 内存定义 ==========
  #define MEM_SIZE 256  // 简化内存，256字节

  typedef struct {
      uint8_t data[MEM_SIZE];  // 每个格子1字节
  } Memory;

  // ========== 指令格式定义 ==========

  // R型指令（寄存器-寄存器运算）
  typedef struct {
      uint8_t opcode;   // 操作码 [6:0]
      uint8_t rd;       // 目标寄存器 [11:7]
      uint8_t funct3;   // 功能码3 [14:12]
      uint8_t rs1;      // 源寄存器1 [19:15]
      uint8_t rs2;      // 源寄存器2 [24:20]
      uint8_t funct7;   // 功能码7 [31:25]
  } R_Type;

  // I型指令（立即数运算）
  typedef struct {
      uint8_t opcode;
      uint8_t rd;
      uint8_t funct3;
      uint8_t rs1;
      int32_t imm;      // 立即数，有符号！
  } I_Type;

  // S型指令（存储指令）
  typedef struct {
      uint8_t opcode;
      uint8_t funct3;
      uint8_t rs1;      // 基址寄存器
      uint8_t rs2;      // 源寄存器
      int32_t imm;      // 地址偏移
  } S_Type;

  // B型指令（分支指令）
  typedef struct {
      uint8_t opcode;
      uint8_t funct3;
      uint8_t rs1;
      uint8_t rs2;
      int32_t imm;      // 分支偏移量
  } B_Type;
  typedef struct{
      uint8_t opcode;
      uint8_t rd;
      int32_t imm;
  } J_Type;
  // ========== 操作码定义 ==========
  #define OP_REG    0x33  // R型指令
  #define OP_IMM    0x13  // I型立即数指令
  #define OP_LOAD   0x03  // 加载指令
  #define OP_STORE  0x23  // 存储指令
  #define OP_BRANCH 0x63  // 分支指
  #define OP_JAL    0x6F
  #define OP_JALR   0x67
  #define OP_BRANCH 0x63
  #define FUNCT3_ADD  0x0
  #define FUNCT3_AND  0x7
  #define FUNCT3_OR   0x6
  #define FUNCT3_XOR  0x4
  #define FUNCT3_SLL  0x1
  #define FUNCT3_SRL  0x5

  #define FUNCT7_ADD  0x00
  #define FUNCT7_SUB  0x20

  // ========== 函数声明 ==========
  // 初始化函数
  void init_cpu(CPU *cpu);
  void init_memory(Memory *mem);
  void print_registers(CPU *cpu);

  // 取指函数
  uint32_t fetch(Memory *mem, uint32_t pc);

  // 解码函数
  void decode_r_type(uint32_t inst, R_Type *r);
  void decode_i_type(uint32_t inst, I_Type *i);
  void decode_s_type(uint32_t inst, S_Type *s);
  void decode_b_type(uint32_t inst, B_Type *b);
  void decode_j_type(uint32_t inst, J_Type *j);
  // 执行函数
  void execute_add(CPU *cpu, R_Type *r);
  void execute_sub(CPU *cpu, R_Type *r);
  void execute_addi(CPU *cpu, I_Type *i);
  void execute_and(CPU *cpu, R_Type *r);
  void execute_andi(CPU *cpu, I_Type *i);
  void execute_ori(CPU *cpu, I_Type *i);
  void execute_xori(CPU *cpu, I_Type *i);
  void execute_slti(CPU *cpu, I_Type *i);
  void execute_sltiu(CPU *cpu, I_Type *i);
  void execute_xor(CPU *cpu, R_Type *r);
  void execute_or(CPU *cpu, R_Type *r);
  void execute_sll(CPU *cpu, R_Type *r);
  void execute_srl(CPU *cpu, R_Type *r);
  void execute_sra(CPU *cpu, R_Type *r);
  void execute_lw(CPU *cpu, Memory *mem, I_Type *r);
  void execute_sw(CPU *cpu, Memory *mem, S_Type *s);
  void execute_beq(CPU *cpu, B_Type *b);
  void execute_bne(CPU *cpu, B_Type *b);
  void execute_bge(CPU *cpu, B_Type *b);
  void execute_blt(CPU *cpu, B_Type *b);
  void execute_jal(CPU *cpu, J_Type *j);
  void execute_jalr(CPU *cpu, I_Type *i);
  void print_step(int step, const char* description);
  void print_cpu_state(CPU *cpu, const char* context);
  void print_execution_summary(void);
  extern int instruction_count;
  extern int branch_taken;
  extern int function_calls;
  #endif // RISCV_H
