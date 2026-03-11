module cpu_top (
      input  clk,
      input  rst,

      // 调试输出
      output [31:0] debug_pc,
      output [31:0] debug_reg_data,
      output [31:0] debug_alu_result,
      output [31:0] debug_mem_data
  );

      // PC寄存器
      reg [31:0] pc;
      reg [31:0] pc_next;

      // 指令和数据信号
      wire [31:0] inst;
      wire [31:0] read_data_mem;
      wire [31:0] write_data_mem;
      wire [31:0] alu_result;
      wire [31:0] rs1_data, rs2_data;
      wire [31:0] imm;
      wire [31:0] alu_a, alu_b;
      wire [31:0] write_data_reg;
      wire alu_zero;

      // 控制信号
      wire [6:0] opcode;
      wire [4:0] rs1, rs2, rd;
      wire [2:0] funct3;
      wire [6:0] funct7;
      wire reg_write, mem_write, mem_read;
      wire [3:0] alu_ctrl;
      wire alu_src, mem_to_reg, branch, jump;

      // 分支/跳转控制
      wire pc_src;
      wire branch_taken;

      // PC更新逻辑
      always @(posedge clk) begin
          if (rst) begin
              pc <= 32'h0;
          end else begin
              pc <= pc_next;
          end
      end

      // PC下一值计算
      always @(*) begin
          if (jump) begin
              if (opcode == 7'b1101111) begin  // JAL
                  pc_next = pc + imm;
              end else begin                    // JALR
                  pc_next = (rs1_data + imm) & ~32'h1;
              end
          end else if (branch_taken) begin
              pc_next = pc + imm;
          end else begin
              pc_next = pc + 32'd4;
          end
      end

      // 分支条件判断
      assign branch_taken = branch & (
          (funct3 == 3'b000 & alu_zero) |      // BEQ
          (funct3 == 3'b001 & ~alu_zero) |     // BNE
          (funct3 == 3'b100 & alu_result[0]) | // BLT
          (funct3 == 3'b101 & ~alu_result[0])  // BGE
      );

      // 数据通路连接
      assign alu_a = rs1_data;
      assign alu_b = alu_src ? imm : rs2_data;
      assign write_data_mem = rs2_data;
      assign write_data_reg = mem_to_reg ? read_data_mem :
                             jump ? (pc + 32'd4) : alu_result;

      // 调试输出
      assign debug_pc = pc;
      assign debug_reg_data = rs1_data;
      assign debug_alu_result = alu_result;
      assign debug_mem_data = read_data_mem;

      // 子模块实例化

      // 指令存储器
      imem instruction_memory (
          .pc(pc),
          .inst(inst)
      );

      // 指令解码器
      decoder instruction_decoder (
          .inst(inst),
          .opcode(opcode),
          .rs1(rs1),
          .rs2(rs2),
          .rd(rd),
          .funct3(funct3),
          .funct7(funct7),
          .imm(imm),
          .reg_write(reg_write),
          .mem_write(mem_write),
          .mem_read(mem_read),
          .alu_ctrl(alu_ctrl),
          .alu_src(alu_src),
          .mem_to_reg(mem_to_reg),
          .branch(branch),
          .jump(jump)
      );

      // 寄存器堆
      regfile register_file (
          .clk(clk),
          .rst(rst),
          .rs1(rs1),
          .rs2(rs2),
          .rd(rd),
          .wd(write_data_reg),
          .we(reg_write),
          .rs1_data(rs1_data),
          .rs2_data(rs2_data)
      );

      // ALU
      alu arithmetic_logic_unit (
          .a(alu_a),
          .b(alu_b),
          .alu_ctrl(alu_ctrl),
          .result(alu_result),
          .zero(alu_zero)
      );

      // 数据存储器
      dmem data_memory (
          .clk(clk),
          .addr(alu_result),
          .write_data(write_data_mem),
          .mem_write(mem_write),
          .mem_read(mem_read),
          .read_data(read_data_mem)
      );

  endmodule
