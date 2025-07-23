// MIT License
// Copyright (c) 2025 Muhammad Owais
// See the LICENSE file in the root of this project for full license information.

module half_adder (
  input wire a,
  input wire b,
  output wire sum,
  output wire carry
);
  assign sum = a ^ b;
  assign carry = a & b;

endmodule
