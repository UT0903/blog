module register #(
    parameter ADDR_W = 64,
    parameter INST_W = 32,
    parameter DATA_W = 64
)(
    input   i_clk,
    input   i_rst_n,
    input                   i_i_valid_inst, // from instruction memory
    input  [ INST_W-1 : 0 ] i_i_inst,       // from instruction memory
    input                   i_d_valid_data, // from data memory
    input  [ DATA_W-1 : 0 ] i_d_data,       // from data memory
    

    output [ DATA_W-1 : 0 ] o_d_data,       // to data memory
    output [ ADDR_W-1 : 0 ] o_d_addr,       // to data memory
    output                  o_d_MemRead,    // to data memory
    output                  o_d_MemWrite,   // to data memory

    output [12 : 0]         o_pc_inst_add,  //to pc
    output                  o_pc_branch,  //to pc
    output                  o_pc_inst_valid, //to pc

    output                  o_finish
);
    //to data mem
    reg [ DATA_W-1 : 0 ]    o_d_data_r, o_d_data_w;
    reg [ ADDR_W-1 : 0 ]    o_d_addr_r, o_d_addr_w;
    reg     o_d_MemRead_r, o_d_MemRead_w;
    reg     o_d_MemWrite_r, o_d_MemWrite_w;
    assign o_d_data = o_d_data_r;
    assign o_d_addr = o_d_addr_r;
    assign o_d_MemRead = o_d_MemRead_r;
    assign o_d_MemWrite = o_d_MemWrite_r;
    
    integer i;
    initial begin
        for(i = 0; i < 32; i++)
            my_reg[i] = 0;
    end

    //to pc
    reg [ INST_W-1 : 0 ] o_pc_inst_add_r, o_pc_inst_add_w;
    reg o_pc_branch_r, o_pc_branch_w;
    reg o_pc_inst_valid_r, o_pc_inst_valid_w;
    assign o_pc_inst_add = o_pc_inst_add_r;
    assign o_pc_branch = o_pc_branch_r;
    assign o_pc_inst_valid = o_pc_inst_valid_r;
    
    //finish
    reg o_finish_r, o_finish_w;
    assign o_finish = o_finish_r;
    
    //clock
    reg [3:0] cs, ns;
    reg wait_sd;

    reg [4:0] rs1, rs2, rd;
    reg [11:0] imm;
    reg [6:0] op;
    reg [2:0] op2;
    reg [DATA_W-1:0] my_reg[0:31];


    always @(*) begin
        if (cs == 7) begin
            o_pc_inst_valid_w = 1;
            wait_sd = 0;
        end else if(i_i_valid_inst) begin
            op = i_i_inst[6:0];
            rs1 = i_i_inst[19:15]; //rs1
            case (op)
                7'b0000011: begin //LD
                    imm = i_i_inst[31:20]; //imm
                    rd = i_i_inst[11:7]; //rd
                    o_d_addr_w = my_reg[rs1] + imm;
                    o_d_MemRead_w = 1;
                    o_d_MemWrite_w = 0;
                    o_pc_inst_valid_w = 0;
                    o_pc_branch_w = 0;
                end
                7'b0100011: begin //SD
                    imm = {i_i_inst[31:25], i_i_inst[11:7]}; //imm
                    rs2 = i_i_inst[24:20];
                    o_d_addr_w = my_reg[rs1] + imm;
                    o_d_data_w = my_reg[rs2];
                    o_d_MemRead_w = 0;
                    o_d_MemWrite_w = 1;
                    o_pc_inst_valid_w = 0;
                    o_pc_branch_w = 0;
                    wait_sd = 1; //wait store for 7 cycle
                end
                7'b1100011: begin
                    rs2 = i_i_inst[24:20];//rs2
                    op2 = i_i_inst[14:12];
                    imm = {i_i_inst[31], i_i_inst[7], i_i_inst[30:25], i_i_inst[11:8]};
                    case(op2)   
                        3'b000: begin //BEQ   
                            if(my_reg[rs1] == my_reg[rs2]) begin
                                o_pc_branch_w = 1;
                                o_pc_inst_add_w = imm << 1;
                            end else 
                                o_pc_branch_w = 0;
                        end
                        3'b001: begin //BNE
                            if(my_reg[rs1] != my_reg[rs2]) begin
                                o_pc_branch_w = 1;
                                o_pc_inst_add_w = imm << 1;
                            end else
                                o_pc_branch_w = 0;
                        end
                    endcase
                    o_pc_inst_valid_w = 1;
                end
                7'b0010011: begin //**I
                    imm = i_i_inst[31:20]; //imm
                    rd = i_i_inst[11:7];
                    op2 = i_i_inst[14:12];
                    case(op2)
                        3'b000: my_reg[rd] = my_reg[rs1] + imm; //ADDI
                        3'b100: my_reg[rd] = my_reg[rs1] ^ imm; //XORI
                        3'b110: my_reg[rd] = my_reg[rs1] | imm; //ORI
                        3'b111: my_reg[rd] = my_reg[rs1] & imm; //ANDI
                        3'b001: my_reg[rd] = my_reg[rs1] << imm; //SLLI
                        3'b101: my_reg[rd] = my_reg[rs1] >> imm; //SRLI
                    endcase
                    o_d_MemRead_w = 0;
                    o_d_MemWrite_w = 0;
                    o_pc_inst_valid_w = 1;
                    o_pc_branch_w = 0;
                end
                7'b0110011: begin
                    rd = i_i_inst[11:7];
                    rs2 = i_i_inst[24:20];
                    op2 = i_i_inst[14:12];
                    case(op2)
                        3'b000: //ADD or SUB
                            my_reg[rd] = (i_i_inst[30])? my_reg[rs1] - my_reg[rs2] : my_reg[rs1] + my_reg[rs2];
                        3'b100: my_reg[rd] = my_reg[rs1] ^ my_reg[rs2]; //XOR
                        3'b110: my_reg[rd] = my_reg[rs1] | my_reg[rs2]; // OR
                        3'b111: my_reg[rd] = my_reg[rs1] & my_reg[rs2]; //AND
                    endcase
                    o_d_MemRead_w = 0;
                    o_d_MemWrite_w = 0;
                    o_pc_inst_valid_w = 1;
                    o_pc_branch_w = 0;
                end
                default: begin
                    o_finish_w = 1;
                    o_d_MemRead_w = 0;
                    o_d_MemWrite_w = 0;
                    o_pc_inst_valid_w = 0;
                    o_pc_branch_w = 0;
                end
            endcase
        end else if(i_d_valid_data) begin
            my_reg[rd] = i_d_data;
            o_pc_inst_valid_w = 1;
            o_pc_branch_w = 0;
            o_d_MemRead_w = 0;
            o_d_MemWrite_w = 0;
        end else begin
            o_d_MemRead_w = 0;
            o_d_MemWrite_w = 0;
            o_pc_inst_valid_w = 0;
            o_pc_branch_w = 0;
        end  
    end

    
    always @(*) begin
        case (cs)
            0: ns = (wait_sd) ? 1 : 0;
            1: ns = 2;
            2: ns = 3;
            3: ns = 4;
            4: ns = 5;
            5: ns = 6;
            6: ns = 7;
            7: ns = 0;
        endcase
    end

    always @(posedge i_clk or negedge i_rst_n)begin
        if(~i_rst_n) begin
            //to data mem 
            o_d_data_r <= 0;
            o_d_addr_r <= 0;
            o_d_MemRead_r <= 0;
            o_d_MemWrite_r <= 0;
            //to pc
            o_pc_inst_add_r <= 0;
            o_pc_branch_r <= 0;
            o_pc_inst_valid_r <= 1;
            wait_sd <= 0;
            //finish
            o_finish_r <= 0;
            cs <= 0;
        end else begin
            //to data mem
            o_d_data_r <= o_d_data_w;
            o_d_addr_r <= o_d_addr_w;
            o_d_MemRead_r <= o_d_MemRead_w;
            o_d_MemWrite_r <= o_d_MemWrite_w;
            //to pc
            o_pc_inst_add_r <= o_pc_inst_add_w; //start pc
            o_pc_branch_r <= o_pc_branch_w;
            o_pc_inst_valid_r <= o_pc_inst_valid_w;
            //finish
            o_finish_r <= o_finish_w;
            cs <= ns;
        end
    end

endmodule