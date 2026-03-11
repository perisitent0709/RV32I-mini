 `timescale 1ns/1ps

  module dmem_tb;
      reg clk;
      reg [31:0] addr;
      reg [31:0] write_data;
      reg mem_write;
      reg mem_read;
      wire [31:0] read_data;

      // 实例化数据存储器
      dmem uut (
          .clk(clk),
          .addr(addr),
          .write_data(write_data),
          .mem_write(mem_write),
          .mem_read(mem_read),
          .read_data(read_data)
      );

      // 时钟生成
      always #10 clk = ~clk;

      initial begin
          // 初始化
          clk = 0;
          addr = 0;
          write_data = 0;
          mem_write = 0;
          mem_read = 0;

          $display("=== DMEM Test Start ===");

          // 等待时钟稳定
          #20;

          // 测试1：写入数据到地址0x00
          $display("\nTest 1: Write 0x12345678 to address 0x00");
          @(posedge clk);
          addr = 32'h00000000;
          write_data = 32'h12345678;
          mem_write = 1;
          mem_read = 0;
          @(posedge clk);
          mem_write = 0;

          // 测试2：从地址0x00读取数据
          $display("\nTest 2: Read from address 0x00");
          addr = 32'h00000000;
          mem_read = 1;
          #1;  // 等待组合逻辑
          $display("Read data: 0x%h (Expected: 0x12345678)", read_data);
          mem_read = 0;

          // 测试3：写入数据到地址0x04
          $display("\nTest 3: Write 0xABCDEF00 to address 0x04");
          @(posedge clk);
          addr = 32'h00000004;
          write_data = 32'hABCDEF00;
          mem_write = 1;
          @(posedge clk);
          mem_write = 0;

          // 测试4：从地址0x04读取数据
          $display("\nTest 4: Read from address 0x04");
          addr = 32'h00000004;
          mem_read = 1;
          #1;
          $display("Read data: 0x%h (Expected: 0xABCDEF00)", read_data);
          mem_read = 0;

          // 测试5：验证地址0x00的数据没有被覆盖
          $display("\nTest 5: Verify address 0x00 still contains originaldata");
          addr = 32'h00000000;
          mem_read = 1;
          #1;
          $display("Read data: 0x%h (Expected: 0x12345678)", read_data);
          mem_read = 0;

          // 测试6：测试地址对齐
          $display("\nTest 6: Test address alignment");
          // 写入非对齐地址（应该映射到对齐地址）
          @(posedge clk);
          addr = 32'h00000009;  // 非对齐地址
          write_data = 32'hDEADBEEF;
          mem_write = 1;
          @(posedge clk);
          mem_write = 0;

          // 从对齐地址读取（应该是同一个字）
          addr = 32'h00000008;  // 对应的对齐地址
          mem_read = 1;
          #1;
          $display("Non-aligned write to 0x09, read from 0x08: 0x%h",read_data);
          mem_read = 0;

          // 测试7：读取未初始化位置
          $display("\nTest 7: Read uninitialized location");
          addr = 32'h00000100;
          mem_read = 1;
          #1;
          $display("Read from 0x100: 0x%h (Expected: 0x00000000)",read_data);
          mem_read = 0;

          $display("\n=== DMEM Test Complete ===");
          $finish;
      end

  endmodule
