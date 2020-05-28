`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/28 20:39:10
// Design Name: 
// Module Name: mux_2to1_vector
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


module mux_2to1_vector
#(
    parameter VECTOR_LEN=16
)
(
    input [VECTOR_LEN-1:0] a,
    input [VECTOR_LEN-1:0] b,
    input sel,
    output reg [VECTOR_LEN-1:0] y
    );
    always @ (a,b,sel)
        case(sel)
            1'b0:y=b;
            1'b1:y=a;
        endcase
endmodule
