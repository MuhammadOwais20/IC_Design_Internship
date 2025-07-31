module V_Counter(
    input clk,
    input reset,
    input [10:0] hcount,      // Needed for line counting
    output reg [9:0] vcount,
    output reg vsync
);

    localparam V_DISPLAY       = 600;
    localparam V_FRONT_PORCH   = 1;
    localparam V_SYNC_PULSE    = 4;
    localparam V_BACK_PORCH    = 23;
    localparam V_TOTAL         = V_DISPLAY + V_FRONT_PORCH + V_SYNC_PULSE + V_BACK_PORCH;

    localparam H_TOTAL = 1056; // Must match the one in H_Counter

    always @(posedge clk or posedge reset) begin
        if (reset)
            vcount <= 0;
        else if (hcount == H_TOTAL - 1) begin
            if (vcount == V_TOTAL - 1)
                vcount <= 0;
            else
                vcount <= vcount + 1;
        end
    end

    always @(posedge clk) begin
        vsync <= ~((vcount >= (V_DISPLAY + V_FRONT_PORCH)) &&
                   (vcount <  (V_DISPLAY + V_FRONT_PORCH + V_SYNC_PULSE)));
    end

endmodule
