#include "riscv.h"

int main() {
    printf("========================================\n");
    printf("  RISC-V Simulator - Day 2 Test\n");
    printf("========================================\n\n");

    // 初始化CPU和内存
    CPU cpu;
    Memory mem;
    init_cpu(&cpu);
    init_memory(&mem);

    // ========== 测试1：ADDI - 加载立即数 ==========
    printf("\n>>> Test 1: ADDI x1, x0, 100\n");
    I_Type i1;
    i1.opcode = 0x13;
    i1.rd = 1;
    i1.rs1 = 0;
    i1.funct3 = 0;
    i1.imm = 100;
    execute_addi(&cpu, &i1);

    // ========== 测试2：ANDI - 按位与 ==========
    printf("\n>>> Test 2: ANDI x2, x1, 0x0F\n");
    I_Type i2;
    i2.opcode = 0x13;
    i2.rd = 2;
    i2.rs1 = 1;
    i2.funct3 = 7;
    i2.imm = 0x0F;
    execute_andi(&cpu, &i2);

    // ========== 测试3：SLL - 左移 ==========
    printf("\n>>> Test 3: SLL x3, x2, x1 (shift by 2)\n");
    cpu.x[1] = 2;  // 设置移位量
    R_Type r1;
    r1.opcode = 0x33;
    r1.rd = 3;
    r1.rs1 = 2;
    r1.rs2 = 1;
    r1.funct3 = 1;
    r1.funct7 = 0;
    execute_sll(&cpu, &r1);

    // ========== 测试4：SW - 存储到内存 ==========
    printf("\n>>> Test 4: SW x3, 0(x0) - Store x3 to memory[0]\n");
    S_Type s1;
    s1.opcode = 0x23;
    s1.rs1 = 0;
    s1.rs2 = 3;
    s1.funct3 = 2;
    s1.imm = 0;
    execute_sw(&cpu, &mem, &s1);

    // ========== 测试5：LW - 从内存加载 ==========
    printf("\n>>> Test 5: LW x4, 0(x0) - Load from memory[0] to x4\n");
    I_Type i3;
    i3.opcode = 0x03;
    i3.rd = 4;
    i3.rs1 = 0;
    i3.funct3 = 2;
    i3.imm = 0;
    execute_lw(&cpu, &mem, &i3);

    // ========== 测试6：SLTI - 有符号比较 ==========
    printf("\n>>> Test 6: SLTI x5, x1, 50 (100 < 50?)\n");
    I_Type i4;
    i4.opcode = 0x13;
    i4.rd = 5;
    i4.rs1 = 1;
    i4.funct3 = 2;
    i4.imm = 50;
    execute_slti(&cpu, &i4);

    printf("\n>>> Test: BEQ x1, x1, 8(相等，应该跳转)\n");
    cpu.x[1] = 10;
    cpu.pc = 0;
    B_Type b1;
    b1.opcode = 0x63;
    b1.funct3 = 0x0;
    b1.rs1 = 1;
    b1.rs2 = 2;
    b1.imm = 8;
    execute_beq(&cpu, &b1);
    printf("Pc after BEQ: 0x%x (expectrd: 0x8)\n", cpu.pc);
    
    printf("\n>>> Test: 斐波那契数)\n");
    cpu.x[1] = 0;
    cpu.x[2] = 1;
    cpu.x[3] = 0;
    cpu.x[4] =9;
    cpu.x[5] = 0;
    cpu.pc = 0;
    while(cpu.x[5]<cpu.x[4]) {
        R_Type r_add;
        r_add.rd =3;
        r_add.rs1 =1;
        r_add.rs2 = 2;
        r_add.funct3 =0;
        r_add.funct7 =0;
        execute_add(&cpu, &r_add);
        
        I_Type i_add;
        i_add.rd = 1;
        i_add.rs1 = 2;
        i_add.imm  = 0;
        i_add.funct3 = 0;
        execute_addi(&cpu, &i_add);

        I_Type i_addi;
        i_addi.rd = 2;
        i_addi.rs1 = 3;
        i_addi.imm  = 0;
        i_addi.funct3 = 0;
        execute_addi(&cpu, &i_addi);
         I_Type i_cnt;
  i_cnt.rd = 5;
  i_cnt.rs1 = 5;
  i_cnt.imm = 1;
  i_cnt.funct3 = 0;
  execute_addi(&cpu, &i_cnt);
    }  printf("sum = %u\n", cpu.x[2]);

    printf("\n>>> Test: 数列加和)\n");
    cpu.x[1] = 0;
    cpu.x[2] =1;
    cpu.x[3] = 11;
    while (cpu.x[2] < cpu.x[3]){
        R_Type r_add;
        r_add.rd = 1;
        r_add.rs1 = 1;
        r_add.rs2 = 2;
        r_add.funct3 = 0;
        r_add.funct7 =0;
        execute_add(&cpu, &r_add);
        
        I_Type i_add;
        i_add.rd = 2;
        i_add.rs1 = 2;
        i_add.imm  = 1;
        i_add.funct3 = 0;
        execute_addi(&cpu, &i_add);
    }
    printf("sum = %u\n", cpu.x[1]);

    printf("\n>>> Test: BLT)\n");
    cpu.x[4] = 3;
    cpu.x[5] = 10;
    cpu.pc = 0;
    B_Type b_blt;
    b_blt.rs1 = 4;
    b_blt.rs2 = 5;
    b_blt.imm = 8;
    execute_blt(&cpu, &b_blt);

    printf("\n>>> Test: BEQ)\n");
    cpu.x[4] = 5;
    cpu.x[5] = 5;
    cpu.pc = 0;
    B_Type b_beq;
    b_beq.rs1 = 4;
    b_beq.rs2 = 5;
    b_beq.imm = 12;
    execute_beq(&cpu,&b_beq);

printf("\n=== Step 1: Function Call Test - multiply(5, 3) ===\n");

  // 重置统计
  instruction_count = 0;
  branch_taken = 0;
  function_calls = 0;

  // 初始化
  init_cpu(&cpu);
  cpu.x[10] = 5;   // 参数a = 5
  cpu.x[11] = 3;   // 参数b = 3
  cpu.pc = 0x1000;
  print_cpu_state(&cpu, "After parameter setup");

  // Step 2: 执行JAL指令
  printf("\n=== Step 2: Execute JAL instruction ===\n");
  J_Type j_call;
  j_call.opcode = OP_JAL;
  j_call.rd = 1;              // x1保存返回地址
  j_call.imm = 0x1000;        // 跳转偏移量
  execute_jal(&cpu, &j_call);
  print_cpu_state(&cpu, "After JAL");

  // Step 3: 执行函数体（循环）
  printf("\n=== Step 3: Execute function body ===\n");
  cpu.x[12] = 0;   // result = 0
  cpu.x[13] = 0;   // i = 0

  while(cpu.x[13] < cpu.x[11]) {
      // result += a
      R_Type r_add;
      r_add.opcode = OP_REG;
      r_add.rd = 12;
      r_add.rs1 = 12;
      r_add.rs2 = 10;
      r_add.funct3 = FUNCT3_ADD;
      r_add.funct7 = FUNCT7_ADD;
      execute_add(&cpu, &r_add);

      // i++
      I_Type i_inc;
      i_inc.opcode = OP_IMM;
      i_inc.rd = 13;
      i_inc.rs1 = 13;
      i_inc.funct3 = FUNCT3_ADD;
      i_inc.imm = 1;
      execute_addi(&cpu, &i_inc);
  }
  print_cpu_state(&cpu, "After function execution");

  // Step 4: 设置返回值并执行JALR
  printf("\n=== Step 4: Execute JALR return ===\n");
  cpu.x[10] = cpu.x[12];  // 返回值
  printf("Setting return value: x10 = x12 = %u\n", cpu.x[10]);

  I_Type i_ret;
  i_ret.opcode = OP_JALR;
  i_ret.rd = 0;     // x0，不保存返回地址
  i_ret.rs1 = 1;    // 跳转到x1的地址
  i_ret.funct3 = 0;
  i_ret.imm = 0;    // 无偏移
  execute_jalr(&cpu, &i_ret);
  print_cpu_state(&cpu, "After JALR return");

  // Step 5: 验证结果
  printf("\n=== Step 5: Verify results ===\n");
  printf("Result: multiply(5, 3) = %u\n", cpu.x[10]);
  printf("Expected: 15\n");
  printf("Success: %s\n", (cpu.x[10] == 15) ? "YES" : "NO");

  print_execution_summary();

    // 打印所有寄存器状态
    print_registers(&cpu);

    /*printf("\n========================================\n");
    printf("  Expected Results:\n");
    printf("  x1 = 2 (0x64)\n");
    printf("  x2 = 4   (100 & 0x0F)\n");
    printf("  x3 = 16  (4 << 2)\n");
    printf("  x4 = 16  (loaded from memory)\n");
    printf("  x5 = 0   (2 < 50 is true)\n");
    printf("========================================\n");*/

    return 0;
}
