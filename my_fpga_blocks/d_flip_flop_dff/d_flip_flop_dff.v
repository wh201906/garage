`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/28 12:43:10
// Design Name: 
// Module Name: d_flip_flop_dff
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


module d_flip_flop_dff(
    input d,
    input clk,
    input prn,
    input clrn,
    output reg q
    );
    always @ (posedge clk)
    begin
        if(prn&clrn==1)
            q<=d;
    end
    
    always @ (prn,clrn)
    begin
        if(prn==0)
            q=1;
        if(clrn==0)
            q=0;
    end
endmodule
