 `timescale 1ns/1ps

  module cpu_top_tb;
      reg clk, rst;
      wire [31:0] debug_pc, debug_reg_data, debug_alu_result,debug_mem_data;

      // 实例化CPU
      cpu_top uut (
          .clk(clk),
          .rst(rst),
          .debug_pc(debug_pc),
          .debug_reg_data(debug_reg_data),
          .debug_alu_result(debug_alu_result),
          .debug_mem_data(debug_mem_data)
      );

      // 时钟生成
      always #10 clk = ~clk;

      initial begin
          $display("=== RISC-V CPU Test Start ===");

          // 初始化
          clk = 0;
          rst = 1;

          // 复位
          #30;
          rst = 0;
          $display("Reset released, CPU starts execution...");

          // 运行几个时钟周期
          repeat(20) begin
              @(posedge clk);
              $display("PC=0x%h | ALU=0x%h | REG=0x%h | MEM=0x%h",
                       debug_pc, debug_alu_result, debug_reg_data,debug_mem_data);

              // 如果PC没有改变，可能是程序结束或卡住
              if ($past(debug_pc) == debug_pc && $time > 50) begin
                  $display("PC not changing, possibly end of program");
                  #100;
                  break;
              end
          end

          // 检查寄存器结果
          $display("\n=== Final Register States ===");
          $display("Expected results based on test program:");
          $display("x1 should be 10");
          $display("x2 should be 20");
          $display("x3 should be 30 (10+20)");
          $display("x4 should be 30 (loaded from memory)");

          $display("\n=== CPU Test Complete ===");
          $finish;
      end

      // 监控重要信号
      initial begin
          $monitor("Time=%0t | PC=0x%h | Inst=0x%h", $time, debug_pc,uut.inst);
      end

  endmodule
