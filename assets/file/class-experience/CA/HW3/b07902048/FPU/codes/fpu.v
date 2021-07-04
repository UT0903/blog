module fpu #(
    parameter DATA_WIDTH = 32,
    parameter INST_WIDTH = 1
)(
    input                   i_clk,
    input                   i_rst_n,
    input  [DATA_WIDTH-1:0] i_data_a,
    input  [DATA_WIDTH-1:0] i_data_b,
    input  [INST_WIDTH-1:0] i_inst,
    input                   i_valid,
    output [DATA_WIDTH-1:0] o_data,
    output                  o_valid
);

    reg [DATA_WIDTH-1:0] o_data_r, o_data_w;
    reg                  o_valid_r, o_valid_w;
    reg [7:0] expo_a, expo_b, expo_r;
    reg [32:0] frac_a, frac_b, frac_r;
    reg sign_a, sign_b, sign_r, sticky;
    integer i;
    reg [23:0] mul_a, mul_b;
    reg [47:0] mul_r;

    assign o_data = o_data_r;
    assign o_valid = o_valid_r;
    
    always @(*) begin
        if (i_valid) begin
            o_valid_w = 1;
            case(i_inst)
                4'd0: begin    
                    //$display("a=%b b=%b", i_data_a, i_data_b);
                    expo_a = i_data_a[30:23];
                    expo_b = i_data_b[30:23];
                    frac_a = {2'b01, i_data_a[22:0], 8'b00000000};
                    frac_b = {2'b01, i_data_b[22:0], 8'b00000000};
                    sign_a = i_data_a[31];
                    sign_b = i_data_b[31];
                    
                    //$display("expo_a=%b expo_b=%b frac_a=%b frac_b=%b", expo_a, expo_b, frac_a, frac_b);
                    //Shift
                    if(expo_a > expo_b) begin
                        frac_b = frac_b >> (expo_a - expo_b);
                        expo_r = expo_a;
                    end else if(expo_a < expo_b) begin
                        frac_a = frac_a >> (expo_b - expo_a);
                        expo_r = expo_b;
                    end else begin
                        expo_r = expo_a;
                    end
                    //$display("expo_r=%b", expo_r);

                    //Add
                    if(sign_a ^ sign_b == 0) begin
                        frac_r = frac_a + frac_b;
                        sign_r = sign_a;
                    end else begin
                        frac_r = (frac_a > frac_b)?frac_a - frac_b:frac_b - frac_a;
                        sign_r = 
                            ((frac_a > frac_b && sign_a) || (frac_a < frac_b && sign_b))?
                            1:0;
                    end
                    //$display("expo_r=%b frac_r=%b sign_r=%b", expo_r, frac_r, sign_r);
                    //Normalize
                    if(frac_r[32]) begin
                        frac_r = frac_r >> 1;
                        expo_r = expo_r + 1;
                    end

                    //Round 110 011
                    sticky = 0;
                    for (i = 0; i < 7; i = i + 1) begin
                        sticky = (sticky | frac_r[i]);
                    end

                    if((frac_r[8] == 1 && frac_r[7] == 1) || (frac_r[7] == 1 && sticky == 1)) begin
                        frac_r = (frac_r >> 8) + 1;
                    end else begin
                        frac_r = (frac_r >> 8);
                    end
                    o_data_w = {sign_r, expo_r, frac_r[22:0]};
                end
                4'd1: begin
                    sign_r = i_data_a[31] ^ i_data_b[31];
                    expo_r = i_data_a[30:23] + i_data_b[30:23] - 127;
                    mul_a = {1'b1, i_data_a[22:0]};
                    mul_b = {1'b1, i_data_b[22:0]};
                    //$display("i_data_a=%b i_data_b=%b", i_data_a, i_data_b);
                    //$display("mul_a=%b mul_b=%b sign_r=%b expo_r=%b", mul_a, mul_b, sign_r, expo_r);
                    //Mul
                    mul_r = mul_a * mul_b;
                    //Shift
                    //$display("%b", mul_r);
                    if(mul_r[47]) begin
                       mul_r = mul_r >> 1;
                       expo_r = expo_r + 1;
                    end
                    //$display("%b", mul_r);
                    //Round 110 011
                    
                    sticky = 0;
                    for (i = 0; i < 22; i++) begin
                        sticky = (sticky | mul_r[i]);
                    end

                    if((mul_r[23] && mul_r[22]) || (mul_r[22] && sticky)) begin
                        mul_r = (mul_r >> 23) + 1;
                    end else begin
                        mul_r = (mul_r >> 23);
                    end
                    o_data_w = {sign_r, expo_r, mul_r[22:0]};
                end
                default: begin
                    o_data_w = 0;
                end
            endcase
        end else begin
            o_data_w = 0;
            o_valid_w = 0;
        end
    end

    always @(posedge i_clk or negedge i_rst_n)begin
        if(~i_rst_n) begin
            o_data_r <= 0;
            o_valid_r <= 0;
        end else begin
            o_data_r <= o_data_w;
            o_valid_r <= o_valid_w;
        end
    end

endmodule