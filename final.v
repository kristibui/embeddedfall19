`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/13/2019 10:44:19 AM
// Design Name: 
// Module Name: final
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


module final(button, clk, S, LEDs, signalout);
input button;
input clk;
output [6:0] S; //for 7-segment display
output [7:0] LEDs;
output signalout;
reg [6:0] S;
reg [7:0] LEDs;
reg signalout;
reg [2:0] progress;
reg [31:0] counter;
reg val1, val2, val;

initial begin
    LEDs = 8'b0000_0000;
    S = 7'b000_0000;
    signalout = 0;
    progress = 3'b000;
end

    always @(posedge clk) begin

        case(progress)

            default: progress = 3'b000;
    
            3'b000: begin
                counter = counter + 1'b1;
                if (counter >= 10) begin
                    progress = 3'b001;
                    val1 = button;
                    counter = 0;
                end
            end
            3'b001: begin
                counter = counter + 1'b1;
                if (counter >= 1000000) begin //wait 10 ms before reading the switch again
                    progress = 3'b010;
                    val2 = button;
                    counter = 0;
                end
            end
            3'b010: begin
                if (val1 == val2 && val != val1) begin
                    progress = 3'b011;
                end
                else begin
                    progress = 3'b000;
                end
            end
            3'b011: begin
                if (val1 == 1) begin
                    LEDs = LEDs + 8'b0000_0001;
                    if (LEDs == 8'b0000_0001)
                        S = 7'b111_1100;
                    else if (LEDs == 8'b0000_0010)
                        S = 7'b011_1110;
                    else if (LEDs == 8'b0000_0011) begin
                        S = 7'b000_0110;
                        LEDs = 8'b0000_0000;
                    end
                    val = 1;
                end
                else begin
                    val = 0;
                end
                counter = 0;
                progress = 3'b000;

            end
        endcase
end

endmodule
