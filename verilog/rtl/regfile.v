module regfile(
    input clk,
    input rst,
    input [4:0] rs1,
    input [4:0] rs2,
    input [4:0] rd,
    input [31:0] wd,
    input we,
    output [31:0] rs1_data,
    output [31:0] rs2_data
);
    reg [31:0] registers [31:0];
    integer i;
    always @(posedge clk) begin
        if (rst) begin
            for (i = 0; i < 32; i =i +1 ) begin
                registers[i] <= 32'h0;
            end
        end else begin
            if (we && (rd != 5'h0)) begin
                registers[rd] <= wd;
            end
        end
    end
    assign rs1_data = (rs1 == 5'h0) ? 32'h0 : registers[rs1];
    assign rs2_data = (rs2 == 5'h0) ? 32'h0 : registers[rs2];
    
endmodule

