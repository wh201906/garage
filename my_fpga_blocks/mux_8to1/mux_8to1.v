`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/02 18:57:18
// Design Name: 
// Module Name: mux_8to1
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


module mux_8to1(
    input d0,
    input d1,
    input d2,
    input d3,
    input d4,
    input d5,
    input d6,
    input d7,
    input a,
    input b,
    input c,
    output reg y
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
