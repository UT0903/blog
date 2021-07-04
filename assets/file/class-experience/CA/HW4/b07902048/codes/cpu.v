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
    output [ DATA_W-1 : 0 ] o_d_w_data,     // to data memory
    output [ ADDR_W-1 : 0 ] o_d_w_addr,     // to data memory
    output [ ADDR_W-1 : 0 ] o_d_r_addr,     // to data memory
    output                  o_d_MemRead,    // to data memory
    output                  o_d_MemWrite,   // to data memory
    output                  o_finish
);
    reg [ DATA_W-1 : 0 ]    o_d_w_data_r, o_d_w_data_w;
    reg [ ADDR_W-1 : 0 ]    o_d_w_addr_r, o_d_w_addr_w;
    reg [ ADDR_W-1 : 0 ]    o_d_r_addr_r, o_d_r_addr_w;
    reg                     o_d_MemRead_r, o_d_MemRead_w;
    reg                     o_d_MemWrite_r, o_d_MemWrite_w;
    reg                     o_i_valid_addr_r, o_i_valid_addr_w;
    reg [ ADDR_W-1 : 0 ]    o_i_addr_r, o_i_addr_w; 
    reg                     o_finish_r, o_finish_w;
    
    
    assign o_i_valid_addr = o_i_valid_addr_r;
    assign o_i_addr = o_i_addr_r;
    assign o_d_w_data = o_d_w_data_r;
    assign o_d_w_addr = o_d_w_addr_r;
    assign o_d_r_addr = o_d_r_addr_r;
    assign o_d_MemRead = o_d_MemRead_r;
    assign o_d_MemWrite = o_d_MemWrite_r;
    assign o_finish = o_finish_r;
    
    reg [ DATA_W-1 : 0 ]    pc;
    reg [DATA_W-1:0]        my_reg_w[0:31], my_reg_r[0:31];
    integer i;
    initial begin
        for(i = 0; i < 32; i++) begin
            my_reg_w[i] = 0;
            my_reg_r[i] = 0;
        end
        wait_sd = 0;
        o_i_addr_w = 0;
        rd_r = 0;
    end

    reg [3:0] cs, ns;
    reg wait_sd;
    reg [4:0] rd_w, rd_r;
    
    always @(*) begin
        for(i = 0; i < 32; i++)
            my_reg_w[i] = my_reg_r[i];
        rd_w = rd_r;
        o_d_r_addr_w = 0;
        o_d_w_addr_w = 0;
        o_d_w_data_w = 0;
        o_finish_w = 0;
        wait_sd = 0;
        o_i_valid_addr_w = 0;
        o_d_MemRead_w = 0;
        o_d_MemWrite_w = 0;
        if (cs == 1) begin
            o_i_valid_addr_w = 1;
            o_i_addr_w = o_i_addr_r + 4;
        end else if(i_i_valid_inst) begin
            case (i_i_inst[6:4])
                3'b000: begin //LD
                    rd_w = i_i_inst[11:7]; //rd
                    o_d_r_addr_w = my_reg_r[i_i_inst[19:15]] + i_i_inst[31:20];
                    o_i_addr_w = o_i_addr_r;
                    o_d_MemRead_w = 1;
                end
                3'b010: begin //SD
                    o_d_w_addr_w = my_reg_r[i_i_inst[19:15]] + {i_i_inst[31:25], i_i_inst[11:7]};
                    o_d_w_data_w = my_reg_r[i_i_inst[24:20]];
                    o_i_addr_w = o_i_addr_r;
                    o_d_MemWrite_w = 1;
                    wait_sd = 1; //wait store for 7 cycle
                end
                3'b110: begin
                    o_i_valid_addr_w = 1;
                    case(i_i_inst[12])   
                        1'b0: begin //BEQ   
                            if(my_reg_r[i_i_inst[19:15]] == my_reg_r[i_i_inst[24:20]]) begin
                                o_i_addr_w = o_i_addr_r + ({{51{i_i_inst[31]}}, i_i_inst[7], i_i_inst[30:25], i_i_inst[11:8]} << 1);
                            end else begin
                                o_i_addr_w = o_i_addr_r + 4;
                            end
                        end
                        1'b1: begin //BNE
                            if(my_reg_r[i_i_inst[19:15]] != my_reg_r[i_i_inst[24:20]]) begin
                                o_i_addr_w = o_i_addr_r + ({{51{i_i_inst[31]}}, i_i_inst[7], i_i_inst[30:25], i_i_inst[11:8]} << 1);
                            end else begin
                                o_i_addr_w = o_i_addr_r + 4;
                            end
                        end
                        default: o_i_addr_w = o_i_addr_r;
                    endcase
                end
                3'b001: begin //**I
                    case(i_i_inst[14:12])
                        3'b000: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] + i_i_inst[31:20]; //ADDI
                        3'b100: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] ^ i_i_inst[31:20]; //XORI
                        3'b110: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] | i_i_inst[31:20]; //ORI
                        3'b111: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] & i_i_inst[31:20]; //ANDI
                        3'b001: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] << i_i_inst[31:20]; //SLLI
                        3'b101: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] >> i_i_inst[31:20]; //SRLI
                        default: my_reg_w[i_i_inst[11:7]] = 0; //should not in
                    endcase
                    o_i_valid_addr_w = 1;
                    o_i_addr_w = o_i_addr_r + 4;
                end
                3'b011: begin
                    case(i_i_inst[14:12])
                        3'b000: //ADD or SUB
                            my_reg_w[i_i_inst[11:7]] = (i_i_inst[30])? my_reg_r[i_i_inst[19:15]] - my_reg_r[i_i_inst[24:20]] : my_reg_r[i_i_inst[19:15]] + my_reg_r[i_i_inst[24:20]];
                        3'b100: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] ^ my_reg_r[i_i_inst[24:20]]; //XOR
                        3'b110: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] | my_reg_r[i_i_inst[24:20]]; // OR
                        3'b111: my_reg_w[i_i_inst[11:7]] = my_reg_r[i_i_inst[19:15]] & my_reg_r[i_i_inst[24:20]]; //AND
                        default: my_reg_w[i_i_inst[11:7]] = 0; //should not in
                    endcase
                    o_i_valid_addr_w = 1;
                    o_i_addr_w = o_i_addr_r + 4;
                end
                default: begin
                    o_i_addr_w = o_i_addr_r;
                    o_finish_w = 1;
                end
            endcase
        end else if(i_d_valid_data) begin
            my_reg_w[rd_r] = i_d_data;
            o_i_valid_addr_w = 1;
            o_i_addr_w = o_i_addr_r + 4;
        end else begin
            o_i_addr_w = o_i_addr_r;
        end  
    end

    
    always @(*) begin
        case (cs)
            0: ns = (wait_sd) ? 1 : 0;
            1: ns = 0;
            default: ns = 0;
        endcase
    end

    always @(posedge i_clk or negedge i_rst_n)begin
        if(~i_rst_n) begin
            //to data mem 
            o_d_w_data_r <= 0;
            o_d_w_addr_r <= 0;
            o_d_r_addr_r <= 0;
            o_d_MemRead_r <= 0;
            o_d_MemWrite_r <= 0;
            o_i_valid_addr_r <= 1;
            o_i_addr_r <= 0;
            //finish
            o_finish_r <= 0;
            cs <= 0;
            rd_r <= 0;
            for(i = 0; i < 32; i++)
                my_reg_r[i] <= 0;
        end else begin
            //to data mem
            o_d_w_data_r <= o_d_w_data_w;
            o_d_w_addr_r <= o_d_w_addr_w;
            o_d_r_addr_r <= o_d_r_addr_w;
            o_d_MemRead_r <= o_d_MemRead_w;
            o_d_MemWrite_r <= o_d_MemWrite_w;
            o_i_valid_addr_r <= o_i_valid_addr_w;
            o_i_addr_r <= o_i_addr_w;
            //finish
            o_finish_r <= o_finish_w;
            cs <= ns;
            rd_r <= rd_w;
            for(i = 0; i < 32; i++)
                my_reg_r[i] <= my_reg_w[i];
        end
    end

endmodule
