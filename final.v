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

// resistor = input from board, corresponds to row, buttonsin
//
module final(buttonsin, clk, S, LEDs, signalout, buttonsout);
input [3:0]buttonsin;//buttons[4] is row 4 and 5 on the keypad
input clk;
output [6:0] S; //for 7-segment display
output [7:0] LEDs;
output signalout;
output [3:0] buttonsout; //buttonsout[0] is column 1 and 8 on keypad
reg [6:0] S;
reg [7:0] LEDs;
reg signalout;
reg [3:0] buttonsout;
reg [2:0] progress;
reg [31:0] counter;
reg [3:0] val1;
reg [3:0] val2;
reg [3:0] val3;
reg [3:0] val4;
reg [3:0] val1a;
reg [3:0] val2a;
reg [3:0] val3a;
reg [3:0] val4a;
reg [3:0] val1b;
reg [3:0] val2b;
reg [3:0] val3b;
reg [3:0] val4b;
reg [15:0] buttonpressed;
initial begin
    LEDs = 8'b0000_0000;
    S = 7'b000_0000;
    signalout = 0;
    progress = 3'b000;
    buttonsout = 4'b1110;
    buttonpressed = 8'b0000_0000;
end

    always @(posedge clk) begin

        case(progress)

            default: progress = 3'b000;

            3'b000: begin
                counter = counter + 1'b1;
                if (counter >= 10 && counter < 20) begin
//                    progress = 3'b001;
//                    buttonpressed = 8'b1000_0000;
                    if (buttonsin != 1111) begin
                        val1a = buttonsin;
                    end
                    buttonsout = 4'b1101;
//                    LEDs = 0 + buttonsin;
//                    counter = 0;
                end
                else if (counter >= 20 && counter < 30) begin
                    if (buttonsin != 1111) begin
                        val2a = buttonsin;
                    end
                    buttonsout = 4'b1011;
                end
                else if (counter >= 30 && counter < 40) begin
                    if (buttonsin != 1111) begin
                        val3a = buttonsin;
                    end
                    buttonsout = 4'b0111;
                end
                else if (counter >= 40 && counter < 50) begin
                    if (buttonsin != 1111) begin
                        val4a = buttonsin;
                    end
                    counter = 0;
                    progress = 3'b001;
                    buttonsout = 4'b1110;
                end
            end                                    
                    
            3'b001: begin
                counter = counter + 1'b1;
                if (counter >= 1000010 && counter < 1000020) begin
                    if (buttonsin != 1111) begin
                        val1b = buttonsin;
                    end
                    buttonsout = 4'b1101;
                end
                else if (counter >= 1000020 && counter < 1000030) begin
                    if (buttonsin != 1111) begin
                        val2b = buttonsin;
                    end
                    buttonsout = 4'b1011;
                end
                else if (counter >= 1000030 && counter < 1000040) begin
                    if (buttonsin != 1111) begin
                        val3b = buttonsin;
                    end
                    buttonsout = 4'b0111;
                end
                else if (counter >= 1000040 && counter < 1000050) begin
                    if (buttonsin != 1111) begin
                        val4b = buttonsin;
                    end
                    counter = 0;
                    progress = 3'b010;
                end
//                if (counter >= 1000000) begin //wait 10 ms before reading the switch again
//                    progress = 3'b010;
////                    buttonsout = 4'b1110;
//                    val1b = buttonsin;
//                    counter = 0;
//                end
            end
            3'b010: begin
                if (val1a == val1b && val1 != val1a) begin
                    progress = 3'b011;
                    buttonpressed = 8'b1110_0000 + val1a;
                    LEDs = buttonpressed;
                end
                else if (val2a == val2b && val2 != val2a) begin
                    progress = 3'b011;
                end
                else if (val3a == val3b && val3 != val3a) begin
                    progress = 3'b011;
                end
                else if (val4a == val4b && val4 != val4a) begin
                     progress = 3'b011;
                end
                else begin
                    progress = 3'b000;
                end
            end
            3'b011: begin
//                buttonpressed = buttonpressed + val1b;
                case(buttonpressed)
                    8'b1110_0000: begin
                        val1 = val1a;
                        LEDs = 8'b0000_0001;
                    end
                    8'b0111_0000: begin
                        val1 = val1a;
                        LEDs = 8'b0000_1010;
                    end
                endcase
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
