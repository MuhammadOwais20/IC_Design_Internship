module vga_controller(
    input clk,           
    input reset,         
    input [15:0] sram_data,  
    output [19:0] sram_address, 
    output hsync,         
    output vsync,         
    output [10:0] hc,
    output [9:0]  vc,
    output  [7:0] red,
    output  [7:0] green,
    output  [7:0] blue,
    output video_on     
);

    H_Counter Horizontal(
        .clk(clk),
        .reset(reset),
        .hcount(hc),
        .hsync(hsync)
    );

    V_Counter Vertical(
        .clk(clk),
        .reset(reset),
        .hcount(hc),
        .vcount(vc),
        .vsync(vsync)
    );

    display_using_sram Addressing(
        .clk(clk),
        .hcount(hc),
        .vcount(vc),
        .H_DISPLAY(800),
        .V_DISPLAY(600),
        .sram_data(sram_data),
        .sram_address(sram_address),
        .red(red),
        .green(green),
        .blue(blue),
        .video_on(video_on)  
    );

endmodule

