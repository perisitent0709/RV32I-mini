 module imem (
      input  [31:0] pc,          // 程序计数器（字节地址）
      output [31:0] inst         // 输出指令
  );

      // 指令存储器：1024条指令，每条32位
      reg [31:0] memory [1023:0];

      // 地址计算：PC是字节地址，指令是4字节对齐
      // 所以指令索引 = PC[11:2]（去掉最低2位，取中间10位）
      wire [9:0] inst_addr = pc[11:2];

      // 读取指令（组合逻辑）
      assign inst = memory[inst_addr];

      // 初始化指令存储器
      initial begin
          // 清零所有指令
          integer i;
          for (i = 0; i < 1024; i = i + 1) begin
              memory[i] = 32'h00000000;  // NOP指令
          end

          // 加载测试程序：简单的加法程序
          // 地址0x000: ADDI x1, x0, 10    # x1 = 10
          memory[0] = 32'h00a00093;       // ADDI x1, x0,: 10

          // 地址0x004: ADDI x2, x0, 20    # x2 = 20
          memory[1] = 32'h01400113;       // ADDI x2, x0, 20

          // 地址0x008: ADD x3, x1, x2     # x3 = x1 + x2
          memory[2] = 32'h002081b3;       // ADD x3, x1, x2

          // 地址0x00C: SW x3, 0(x0)       # Memory[0] = x3
          memory[3] = 32'h00302023;       // SW x3, 0(x0)

          // 地址0x010: LW x4, 0(x0)       # x4 = Memory[0]
          memory[4] = 32'h00002203;       // LW x4, 0(x0)

          $display("IMEM initialized with test program");
      end

  endmodule
