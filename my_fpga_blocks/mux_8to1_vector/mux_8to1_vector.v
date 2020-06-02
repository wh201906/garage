`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/02 19:05:53
// Design Name: 
// Module Name: mux_8to1_vector
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module mux_8to1_vector
#(
    parameter VECTOR_LEN=16
)
(
    input a,
    input b,
    input c,
    input [VECTOR_LEN-1:0] d0,
    input [VECTOR_LEN-1:0] d1,
    input [VECTOR_LEN-1:0] d2,
    input [VECTOR_LEN-1:0] d3,
    input [VECTOR_LEN-1:0] d4,
    input [VECTOR_LEN-1:0] d5,
    input [VECTOR_LEN-1:0] d6,
    input [VECTOR_LEN-1:0] d7,
    output reg [VECTOR_LEN-1:0] y
    );
    always @ (a,b,c,d0,d1,d2,d3,d4,d5,d6,d7)
        case({c,b,a})
        3'b000:y=d0;
        3'b001:y=d1;
        3'b010:y=d2;
        3'b011:y=d3;
        3'b100:y=d4;
        3'b101:y=d5;
        3'b110:y=d6;
        3'b111:y=d7;
        endcase
endmodule
