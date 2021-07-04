module cpu #( // Do not modify interface
	parameter ADDR_W = 64,
	parameter INST_W = 32,
	parameter DATA_W = 64
)(
    input                   i_clk,
    input                   i_rst_n,
    input                   i_i_valid_inst, // from instruction memory
    input  [ INST_W-1 : 0 ] i_i_inst,       // from instruction memory
    input                   i_d_valid_data, // from data memory
    input  [ DATA_W-1 : 0 ] i_d_data,       // from data memory
    output                  o_i_valid_addr, // to instruction memory
    output [ ADDR_W-1 : 0 ] o_i_addr,       // to instruction memory
    output [ DATA_W-1 : 0 ] o_d_data,       // to data memory
    output [ ADDR_W-1 : 0 ] o_d_addr,       // to data memory
    output                  o_d_MemRead,    // to data memory
    output                  o_d_MemWrite,   // to data memory
    output                  o_finish
);
    wire vaild_pc;
    wire [ 12 : 0] inst_add_pc;
    wire branch_pc;
    pc #(
        .ADDR_W(ADDR_W),
        .DATA_W(DATA_W)
    ) my_pc (
        .i_clk(i_clk),
        .i_rst_n(i_rst_n),
        .i_valid(vaild_pc),
        .i_pc_inst_add(inst_add_pc),
        .i_branch(branch_pc),
        
        .o_i_valid_addr(o_i_valid_addr),
        .o_i_addr(o_i_addr)
    );

    register #(
        .ADDR_W(ADDR_W),
        .INST_W(INST_W),
        .DATA_W(DATA_W)
    ) my_reg (
        .i_clk(i_clk),
        .i_rst_n(i_rst_n),
        .i_i_valid_inst(i_i_valid_inst),
        .i_i_inst(i_i_inst),
        .i_d_valid_data(i_d_valid_data),
        .i_d_data(i_d_data),
        
        .o_d_data(o_d_data),
        .o_d_addr(o_d_addr),
        .o_d_MemRead(o_d_MemRead),
        .o_d_MemWrite(o_d_MemWrite),
        .o_pc_inst_add(inst_add_pc),
        .o_pc_branch(branch_pc),
        .o_pc_inst_valid(vaild_pc),
        .o_finish(o_finish)
    );


endmodule
