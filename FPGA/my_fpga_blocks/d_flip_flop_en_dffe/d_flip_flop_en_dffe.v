`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/05/28 14:00:18
// Design Name: 
// Module Name: d_flip_flop_en_dffe
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


module d_flip_flop_en_dffe(
    input clk,
    input d,
    input ena,
    input prn,
    input clrn,
    output reg q
    );
    always @ (posedge clk)
    begin
        if(ena==0)
            q<=0;
        else
        begin
            if(prn&clrn==1)
                q<=d;
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
