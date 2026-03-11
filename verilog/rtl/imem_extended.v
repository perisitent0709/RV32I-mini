module imem_extended (
    input  [31:0] pc,
    output [31:0] inst
);

    reg [31:0] memory [1023:0];
    wire [9:0] inst_addr = pc[11:2];

    assign inst = memory[inst_addr];

    initial begin
        integer i;
        for (i = 0; i < 1024; i = i + 1) begin
            memory[i] = 32'h00000000;  // NOP
        end

        // ===== 测试程序1：基础算术运算 =====
        $display("Loading Test Program 1: Basic Arithmetic");

        // 0x000: ADDI x1, x0, 10     # x1 = 10
        memory[0] = 32'h00a00093;

        // 0x004: ADDI x2, x0, 20     # x2 = 20
        memory[1] = 32'h01400113;

        // 0x008: ADD x3, x1, x2      # x3 = x1 + x2 = 30
        memory[2] = 32'h002081b3;

        // 0x00C: SUB x4, x3, x1      # x4 = x3 - x1 = 20
        memory[3] = 32'h40118233;

        // ===== 测试程序2：逻辑运算 =====
        // 0x010: ANDI x5, x1, 15     # x5 = x1 & 15 = 10
        memory[4] = 32'h00f0f293;

        // 0x014: ORI x6, x1, 5       # x6 = x1 | 5 = 15
        memory[5] = 32'h0050e313;

        // 0x018: XOR x7, x1, x2      # x7 = x1 ^ x2
        memory[6] = 32'h0020c3b3;

        // ===== 测试程序3：内存操作 =====
        // 0x01C: SW x3, 0(x0)        # Memory[0] = x3 = 30
        memory[7] = 32'h00302023;

        // 0x020: SW x4, 4(x0)        # Memory[4] = x4 = 20
        memory[8] = 32'h00402223;

        // 0x024: LW x8, 0(x0)        # x8 = Memory[0] = 30
        memory[9] = 32'h00002403;

        // 0x028: LW x9, 4(x0)        # x9 = Memory[4] = 20
        memory[10] = 32'h00402483;

        // ===== 测试程序4：移位运算 =====
        // 0x02C: ADDI x10, x0, 2     # x10 = 2 (移位量)
        memory[11] = 32'h00200513;

        // 0x030: SLL x11, x1, x10    # x11 = x1 << 2 = 10 << 2 = 40
        memory[12] = 32'h00a09593;

        // 0x034: SRL x12, x3, x10    # x12 = x3 >> 2 = 30 >> 2 = 7
        memory[13] = 32'h00a1d613;

        // ===== 测试程序5：分支指令 =====
        // 0x038: BEQ x1, x1, 8       # 相等，应该跳转到0x040
        memory[14] = 32'h00108463;

        // 0x03C: ADDI x13, x0, 99    # 不应该执行（被跳过）
        memory[15] = 32'h06300693;

        // 0x040: ADDI x14, x0, 88    # 跳转目标，应该执行
        memory[16] = 32'h05800713;

        // 0x044: BNE x1, x2, 8       # 不等，应该跳转到0x04C
        memory[17] = 32'h00209463;

        // 0x048: ADDI x15, x0, 77    # 不应该执行
        memory[18] = 32'h04d00793;

        // 0x04C: ADDI x16, x0, 66    # 跳转目标
        memory[19] = 32'h04200813;

        // ===== 结束程序 =====
        // 0x050: 后续指令为NOP，程序结束

        $display("Test program loaded:");
        $display("- Basic arithmetic: ADD, SUB, ADDI");
        $display("- Logic operations: AND, OR, XOR");
        $display("- Memory operations: LW, SW");
        $display("- Shift operations: SLL, SRL");
        $display("- Branch operations: BEQ, BNE");
        $display("Total instructions loaded: 20");
    end

endmodule
