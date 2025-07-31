module H_Counter(
    input clk,
    input reset, 
    output reg [10:0] hcount,
    output reg hsync
);

    localparam H_DISPLAY       = 800;
    localparam H_FRONT_PORCH   = 40;
    localparam H_SYNC_PULSE    = 128;
    localparam H_BACK_PORCH    = 88;
    localparam H_TOTAL         = H_DISPLAY + H_FRONT_PORCH + H_SYNC_PULSE + H_BACK_PORCH;

    always @(posedge clk or posedge reset) begin
        if (reset)
            hcount <= 0;
        else if (hcount == H_TOTAL - 1)
            hcount <= 0;
        else
            hcount <= hcount + 1;
    end

    // HSYNC generation
    always @(posedge clk) begin
        hsync <= ~((hcount >= (H_DISPLAY + H_FRONT_PORCH)) &&
                   (hcount <  (H_DISPLAY + H_FRONT_PORCH + H_SYNC_PULSE)));
    end

endmodule

