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


module final(buttons, clk, S, LEDs, signalout, buttonsout);
input [3:0]buttons;
input clk;
output [6:0] S; //for 7-segment display
output [7:0] LEDs;
output signalout;
output [3:0] buttonsout;
reg [6:0] S;
reg [7:0] LEDs;
reg signalout;
reg [3:0] buttonsout;
reg [2:0] progress;
reg [31:0] counter;
reg val1, val2, val3, val4;
reg val1a, val2a, val3a, val4a;
reg val1b, val2b, val3b, val4b;
reg buttonpressed;
initial begin
    LEDs = 8'b0000_0000;
    S = 7'b000_0000;
    signalout = 0;
    progress = 3'b000;
    buttonsout = 4'b0000;
    buttonpressed = 8'b0000_0000;
end

    always @(posedge clk) begin

        case(progress)

            default: progress = 3'b000;
    
            3'b000: begin
                counter = counter + 1'b1;
                if (counter >= 10) begin
                    progress = 3'b001;
                    buttonsout = 4'b0111;
                    buttonpressed = 8'b1000_0000;
                    val1a = buttons;
                    counter = 0;
                end
            end
            3'b001: begin
                counter = counter + 1'b1;
                if (counter >= 1000000) begin //wait 10 ms before reading the switch again
                    progress = 3'b010;
                    buttonsout = 4'b0111;
                    val1b = buttons;
                    counter = 0;
                end
            end
            3'b010: begin
                if (val1a == val1b && val1 != val1a) begin
                    progress = 3'b011;
                end
                else begin
                    progress = 3'b000;
                end
            end
            3'b011: begin
                buttonpressed = buttonpressed + val1b;
                LEDs = buttonpressed;
//                case(buttons)     
//                    4'b0111: begin
//                        LEDs = 8'b0000_0001;
//                    end
                    
//                    4'b1011: begin
//                        LEDs = 8'b0000_0010;
//                    end
                    
//                    4'b1101: begin
//                        LEDs = 8'b0000_0100;
//                    end
                    
//                    4'b1110: begin
//                        LEDs = 8'b0000_1000;
//                    end
//                endcase
//                if (val1 == 1) begin
//                    LEDs = LEDs + 8'b0000_0001;
//                    if (LEDs == 8'b0000_0001)
//                        S = 7'b111_1100;
//                    else if (LEDs == 8'b0000_0010)
//                        S = 7'b011_1110;
//                    else if (LEDs == 8'b0000_0011) begin
//                        S = 7'b000_0110;
//                        LEDs = 8'b0000_0000;
//                    end
//                    val = 1;
//                end
//                else begin
//                    val = 0;
//                end
                counter = 0;
                progress = 3'b000;

            end
        endcase
end

endmodule
