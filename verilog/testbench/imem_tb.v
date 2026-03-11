 `timescale 1ns/1ps

  module imem_tb;
      reg [31:0] pc;
      wire [31:0] inst;

      // 实例化指令存储器
      imem uut (
          .pc(pc),
          .inst(inst)
      );

      initial begin
          $display("=== IMEM Test Start ===");

          // 测试不同PC值
          pc = 32'h00000000;  // 地址0
          #10;
          $display("PC=0x%h: inst=0x%h", pc, inst);

          pc = 32'h00000004;  // 地址4
          #10;
          $display("PC=0x%h: inst=0x%h", pc, inst);

          pc = 32'h00000008;  // 地址8
          #10;
          $display("PC=0x%h: inst=0x%h", pc, inst);

          pc = 32'h0000000C;  // 地址12
          #10;
          $display("PC=0x%h: inst=0x%h", pc, inst);

          pc = 32'h00000010;  // 地址16
          #10;
          $display("PC=0x%h: inst=0x%h", pc, inst);

          // 测试地址对齐
          pc = 32'h00000001;  // 非对齐地址
          #10;
          $display("PC=0x%h: inst=0x%h (should be same as PC=0x00)", pc,
  inst);

          $display("=== IMEM Test Complete ===");
          $finish;
      end

  endmodule
