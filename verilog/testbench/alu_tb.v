`timescale 1ns/1ps

module alu_tb;
      // 测试台信号
      reg [31:0] a, b;
      reg [3:0] alu_ctrl;
      wire [31:0] result;
      wire zero;

      // 实例化ALU
      alu uut (
          .a(a),
          .b(b),
          .alu_ctrl(alu_ctrl),
          .result(result),
          .zero(zero)
      );

      // 测试过程
      initial begin
          $display("=== ALU Test Start ===");

          // 测试加法
          $display("\nTest 1: Addition");
          a = 32'h00000010;  // 16
          b = 32'h00000005;  // 5
          alu_ctrl = 4'b0000; // ADD
          #10;
          $display("16 + 5 = %d (Expected: 21), zero=%b", result, zero);

          // 测试减法
          $display("\nTest 2: Subtraction");
          a = 32'h00000010;  // 16
          b = 32'h00000005;  // 5
          alu_ctrl = 4'b0001; // SUB
          #10;
          $display("16 - 5 = %d (Expected: 11), zero=%b", result, zero);

          // 测试零标志
          $display("\nTest 3: Zero flag");
          a = 32'h00000005;  // 5
          b = 32'h00000005;  // 5
          alu_ctrl = 4'b0001; // SUB
          #10;
          $display("5 - 5 = %d (Expected: 0), zero=%b (Expected: 1)",
  result, zero);

          // 测试按位与
          $display("\nTest 4: Bitwise AND");
          a = 32'h0000000F;  // 15 (1111)
          b = 32'h000000F0;  // 240 (11110000)
          alu_ctrl = 4'b0010; // AND
          #10;
          $display("0x0F & 0xF0 = 0x%h (Expected: 0x00)", result);

          // 测试左移
          $display("\nTest 5: Logical Left Shift");
          a = 32'h00000001;  // 1
          b = 32'h00000004;  // 4 (移位量)
          alu_ctrl = 4'b0101; // SLL
          #10;
          $display("1 << 4 = %d (Expected: 16)", result);

          // 测试右移
          $display("\nTest 6: Logical Right Shift");
          a = 32'h00000010;  // 16
          b = 32'h00000002;  // 2 (移位量)
          alu_ctrl = 4'b0110; // SRL
          #10;
          $display("16 >> 2 = %d (Expected: 4)", result);

          // 测试小于比较
          $display("\nTest 7: Set Less Than");
          a = 32'h00000005;  // 5
          b = 32'h00000010;  // 16
          alu_ctrl = 4'b1000; // SLT
          #10;
          $display("5 < 16 = %d (Expected: 1)", result);

          $display("\n=== ALU Test Complete ===");
          $finish;
      end

  endmodule
