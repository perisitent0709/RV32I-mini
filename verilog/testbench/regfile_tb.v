 module regfile_tb;
      // 测试台信号声明
      reg clk;
      reg rst;
      reg [4:0] rs1, rs2, rd;
      reg [31:0] wd;
      reg we;
      wire [31:0] rs1_data, rs2_data;

      // 实例化被测模块
      regfile uut (
          .clk(clk),
          .rst(rst),
          .rs1(rs1),
          .rs2(rs2),
          .rd(rd),
          .wd(wd),
          .we(we),
          .rs1_data(rs1_data),
          .rs2_data(rs2_data)
      );

      // 时钟生成：每10ns翻转一次，周期20ns
      always #10 clk = ~clk;

        // 开启波形数据转储
      initial begin
          $dumpfile("wave_dump.vcd"); // 指定要生成的文件名
          $dumpvars(0, regfile_tb);   // 记录 regfile_tb 顶层及其所有内部信号的变化
      end

      // 测试过程
      initial begin
          // 初始化信号
          clk = 0;
          rst = 1;
          rs1 = 0;
          rs2 = 0;
          rd = 0;
          wd = 0;
          we = 0;

          // 输出测试开始信息
          $display("=== RegFile Test Start ===");

          // 复位测试
          #20;  // 等待一个时钟周期
          rst = 0;
          #20;

          // 测试1：写入x1寄存器
          $display("\nTest 1: Write 0x12345678 to x1");
          @(posedge clk);
          rd = 5'd1;           // 写入x1
          wd = 32'h12345678;   // 写入数据
          we = 1;              // 写使能
          @(posedge clk);
          we = 0;              // 关闭写使能

          // 验证写入结果
          rs1 = 5'd1;          // 读取x1
          #1;                  // 等待组合逻辑稳定
          $display("Read x1: 0x%h (Expected: 0x12345678)", rs1_data);

          // 测试2：写入x2寄存器
          $display("\nTest 2: Write 0xABCDEF00 to x2");
          @(posedge clk);
          rd = 5'd2;
          wd = 32'hABCDEF00;
          we = 1;
          @(posedge clk);
          we = 0;

          // 验证写入结果
          rs1 = 5'd2;
          #1;
          $display("Read x2: 0x%h (Expected: 0xABCDEF00)", rs1_data);

          // 测试3：同时读取两个寄存器
          $display("\nTest 3: Read x1 and x2 simultaneously");
          rs1 = 5'd1;
          rs2 = 5'd2;
          #1;
          $display("rs1_data (x1): 0x%h", rs1_data);
          $display("rs2_data (x2): 0x%h", rs2_data);

          // 测试4：尝试写入x0（应该无效）
          $display("\nTest 4: Try to write to x0 (should be ignored)");
          @(posedge clk);
          rd = 5'd0;           // 尝试写入x0
          wd = 32'hDEADBEEF;   // 任意数据
          we = 1;
          @(posedge clk);
          we = 0;

          // 验证x0仍然为0
          rs1 = 5'd0;
          #1;
          $display("Read x0: 0x%h (Expected: 0x00000000)", rs1_data);

          // 测试5：读取未初始化的寄存器
          $display("\nTest 5: Read uninitialized register x5");
          rs1 = 5'd5;
          #1;
          $display("Read x5: 0x%h (Expected: 0x00000000)", rs1_data);

          // 测试6：复位功能
          $display("\nTest 6: Reset functionality");
          rst = 1;
          #20;
          rst = 0;
          #20;

          // 验证复位后所有寄存器为0
          rs1 = 5'd1;
          rs2 = 5'd2;
          #1;
          $display("After reset - x1: 0x%h, x2: 0x%h (Both should be 0)",
  rs1_data, rs2_data);

          $display("\n=== RegFile Test Complete ===");
          $finish;
      end

      // 监控重要信号变化
      initial begin
          $monitor("Time=%0t | clk=%b rst=%b | rd=%d wd=0x%h we=%b | rs1=%d rs1_data=0x%h | rs2=%d rs2_data=0x%h",$time, clk, rst, rd, wd, we, rs1, rs1_data, rs2,rs2_data);
      end

  endmodule
