  module decoder (
      input  [31:0] inst,         // 32位输入指令

      // 解码输出的指令字段
      output [6:0]  opcode,       // 操作码
      output [4:0]  rs1,          // 源寄存器1
      output [4:0]  rs2,          // 源寄存器2
      output [4:0]  rd,           // 目标寄存器
      output [2:0]  funct3,       // 功能码3
      output [6:0]  funct7,       // 功能码7
      output [31:0] imm,          // 立即数（符号扩展后）

      // 控制信号输出
      output reg reg_write,       // 寄存器写使能
      output reg mem_write,       // 内存写使能
      output reg mem_read,        // 内存读使能
      output reg [3:0] alu_ctrl,  // ALU控制信号
      output reg alu_src,       //ALU第二操作数选择（0=寄存器，1=立即数）
      output reg mem_to_reg,      // 写回数据选择（0=ALU结果，1=内存数据）
      output reg branch,          // 分支指令标志
      output reg jump             // 跳转指令标志
  );

      // 指令格式字段提取
      assign opcode = inst[6:0];
      assign rd     = inst[11:7];
      assign funct3 = inst[14:12];
      assign rs1    = inst[19:15];
      assign rs2    = inst[24:20];
      assign funct7 = inst[31:25];

      // 操作码定义
      localparam OP_REG    = 7'b0110011;  // R型指令
      localparam OP_IMM    = 7'b0010011;  // I型立即数指令
      localparam OP_LOAD   = 7'b0000011;  // 加载指令
      localparam OP_STORE  = 7'b0100011;  // 存储指令
      localparam OP_BRANCH = 7'b1100011;  // 分支指令
      localparam OP_JAL    = 7'b1101111;  // JAL指令
      localparam OP_JALR   = 7'b1100111;  // JALR指令

      // ALU控制信号定义
      localparam ALU_ADD  = 4'b0000;
      localparam ALU_SUB  = 4'b0001;
      localparam ALU_AND  = 4'b0010;
      localparam ALU_OR   = 4'b0011;
      localparam ALU_XOR  = 4'b0100;
      localparam ALU_SLL  = 4'b0101;
      localparam ALU_SRL  = 4'b0110;
      localparam ALU_SRA  = 4'b0111;

      // 立即数生成逻辑
      reg [31:0] imm_i, imm_s, imm_b, imm_u, imm_j;

      always @(*) begin
          // I型立即数：[31:20]
          imm_i = {{20{inst[31]}}, inst[31:20]};

          // S型立即数：[31:25] + [11:7]
          imm_s = {{20{inst[31]}}, inst[31:25], inst[11:7]};

          // B型立即数：[31] + [7] + [30:25] + [11:8] + 0
          imm_b = {{19{inst[31]}}, inst[31], inst[7], inst[30:25],
  inst[11:8], 1'b0};

          // U型立即数：[31:12] + 12个0
          imm_u = {inst[31:12], 12'b0};

          // J型立即数：[31] + [19:12] + [20] + [30:21] + 0
          imm_j = {{11{inst[31]}}, inst[31], inst[19:12], inst[20],
  inst[30:21], 1'b0};
      end

      // 根据指令类型选择立即数
      always @(*) begin
          case (opcode)
              OP_IMM, OP_LOAD, OP_JALR: imm = imm_i;
              OP_STORE:                  imm = imm_s;
              OP_BRANCH:                 imm = imm_b;
              OP_JAL:                    imm = imm_j;
              default:                   imm = 32'h0;
          endcase
      end

      // 主控制逻辑
      always @(*) begin
          // 默认值
          reg_write = 0;
          mem_write = 0;
          mem_read = 0;
          alu_ctrl = ALU_ADD;
          alu_src = 0;
          mem_to_reg = 0;
          branch = 0;
          jump = 0;

          case (opcode)
              OP_REG: begin  // R型指令
                  reg_write = 1;
                  alu_src = 0;  // 使用寄存器
                  case ({funct7, funct3})
                      {7'b0000000, 3'b000}: alu_ctrl = ALU_ADD;  // ADD
                      {7'b0100000, 3'b000}: alu_ctrl = ALU_SUB;  // SUB
                      {7'b0000000, 3'b111}: alu_ctrl = ALU_AND;  // AND
                      {7'b0000000, 3'b110}: alu_ctrl = ALU_OR;   // OR
                      {7'b0000000, 3'b100}: alu_ctrl = ALU_XOR;  // XOR
                      {7'b0000000, 3'b001}: alu_ctrl = ALU_SLL;  // SLL
                      {7'b0000000, 3'b101}: alu_ctrl = ALU_SRL;  // SRL
                      {7'b0100000, 3'b101}: alu_ctrl = ALU_SRA;  // SRA
                      default: alu_ctrl = ALU_ADD;
                  endcase
              end

              OP_IMM: begin  // I型立即数指令
                  reg_write = 1;
                  alu_src = 1;  // 使用立即数
                  case (funct3)
                      3'b000: alu_ctrl = ALU_ADD;  // ADDI
                      3'b111: alu_ctrl = ALU_AND;  // ANDI
                      3'b110: alu_ctrl = ALU_OR;   // ORI
                      3'b100: alu_ctrl = ALU_XOR;  // XORI
                      3'b001: alu_ctrl = ALU_SLL;  // SLLI
                      3'b101: begin
                          if (funct7 == 7'b0000000)
                              alu_ctrl = ALU_SRL;  // SRLI
                          else
                              alu_ctrl = ALU_SRA;  // SRAI
                      end
                      default: alu_ctrl = ALU_ADD;
                  endcase
              end

              OP_LOAD: begin  // 加载指令
                  reg_write = 1;
                  mem_read = 1;
                  alu_src = 1;      // 地址计算用立即数
                  mem_to_reg = 1;   // 写回内存数据
                  alu_ctrl = ALU_ADD;
              end

              OP_STORE: begin  // 存储指令
                  mem_write = 1;
                  alu_src = 1;      // 地址计算用立即数
                  alu_ctrl = ALU_ADD;
              end

              OP_BRANCH: begin  // 分支指令
                  branch = 1;
                  alu_ctrl = ALU_SUB;  // 比较用减法
              end

              OP_JAL: begin  // JAL指令
                  reg_write = 1;
                  jump = 1;
              end

              OP_JALR: begin  // JALR指令
                  reg_write = 1;
                  jump = 1;
                  alu_src = 1;      // 地址计算用立即数
                  alu_ctrl = ALU_ADD;
              end

              default: begin
                  // NOP或未知指令，保持默认值
              end
          endcase
      end

  endmodule
