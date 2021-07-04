module pc #(
	parameter ADDR_W = 64,
	parameter DATA_W = 64
)(
	input                   i_clk,
    input                   i_rst_n,
    input					i_valid,
    input  [12 : 0]			i_pc_inst_add,
    input					i_branch, //branch or not

    output                  o_i_valid_addr,
    output [ ADDR_W-1 : 0 ] o_i_addr
);
	reg o_i_valid_addr_r, o_i_valid_addr_w;
	reg [ ADDR_W-1 : 0 ] o_i_addr_r, o_i_addr_w; 
	reg [ DATA_W-1 : 0 ] pc_cnt = 0;
	
    assign o_i_valid_addr = o_i_valid_addr_r;
	assign o_i_addr = o_i_addr_r;

	always @(*) begin
		if (i_valid) begin
            o_i_addr_w = (i_branch)? pc_cnt - 4 + i_pc_inst_add: pc_cnt;
            pc_cnt = o_i_addr_w + 4;
            o_i_valid_addr_w = 1;
		end else
			o_i_valid_addr_w = 0;
	end

	always @(posedge i_clk or negedge i_rst_n)begin
        if(~i_rst_n) begin
            o_i_valid_addr_r <= 0;
            o_i_addr_r <= 0;
        end else begin
            o_i_valid_addr_r <= o_i_valid_addr_w;
            o_i_addr_r <= o_i_addr_w;
        end
    end

endmodule