`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/28 13:09:11
// Design Name: 
// Module Name: jk_flip_flop_jkff
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


module jk_flip_flop_jkff(
    input j,
    input k,
    input clk,
    input prn,
    input clrn,
    output reg q
    );

    always @ (posedge clk,j,k,prn,clrn)
    begin
        if(prn&clrn==1)
        begin
            if(j==1&&k==1)
                q<=~q;
            else if(j==0&&k==1)
                q<=0;
            else if(j==0&&k==1)
                q<=1;
            else
                q<=q;
        end
    end
    always @ (prn,clrn)
    begin
        if(prn==0)
            q=1;
        if(clrn==0)
            q=0;
    end
endmodule
