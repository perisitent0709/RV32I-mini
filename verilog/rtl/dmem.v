 module dmem (
      input  clk,                 // 时钟
      input  [31:0] addr,         // 内存地址（字节地址）
      input  [31:0] write_data,   // 写入数据
      input  mem_write,           // 写使能信号
      input  mem_read,            // 读使能信号
      output [31:0] read_data     // 读出数据
  );

      // 数据存储器：1024字节 = 256个32位字
      reg [31:0] memory [255:0];

      // 地址转换：字节地址转换为字地址
      // addr[9:2] 提取字地址（去掉最低2位）
      wire [7:0] word_addr = addr[9:2];

      // 写操作：同步写入（时钟上升沿）
      always @(posedge clk) begin
          if (mem_write) begin
              memory[word_addr] <= write_data;
              $display("[DMEM] Write: addr=0x%h, data=0x%h", addr,
  write_data);
          end
      end

      // 读操作：组合逻辑，立即输出
      assign read_data = mem_read ? memory[word_addr] : 32'h0;

      // 初始化存储器
      initial begin
          integer i;
          for (i = 0; i < 256; i = i + 1) begin
              memory[i] = 32'h00000000;
          end
          $display("DMEM initialized: 1024 bytes (256 words)");
      end

      // 调试：监控内存访问
      always @(posedge clk) begin
          if (mem_read) begin
              $display("[DMEM] Read: addr=0x%h, data=0x%h", addr,
  read_data);
          end
      end

  endmodule

