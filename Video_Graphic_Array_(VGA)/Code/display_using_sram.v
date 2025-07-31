module display_using_sram(
    input [10:0] hcount,
    input [9:0] vcount,
    input [10:0] H_DISPLAY,
    input [9:0] V_DISPLAY,
    input clk,
    input [15:0] sram_data,
    output [19:0] sram_address,
    output reg [7:0] red,
    output reg [7:0] green,
    output reg [7:0] blue
);

    wire display_area = (hcount < H_DISPLAY) && (vcount < V_DISPLAY);

    assign sram_address = vcount * H_DISPLAY + hcount;

    always @(posedge clk) begin
        if (display_area) begin
            red   <= {sram_data[15:11], 3'b000};
            green <= {sram_data[10:5],  2'b00};
            blue  <= {sram_data[4:0],   3'b000};
        end else begin
            red <= 0;
            green <= 0;
            blue <= 0;
        end
    end

endmodule
