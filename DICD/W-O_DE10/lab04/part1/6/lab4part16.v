`timescale 1 ns/ 10 ps

module lab4part16(clk, WR, CS, In, Out, address_in, address_out);
input clk, WR, CS;
input[7:0] In;
input[3:0] address_in, address_out;
output reg[7:0] Out;
reg[7:0] RAM[0:15];

always @ (posedge clk) begin
	if(CS)
	begin 
		if(WR)
			RAM[address_in] <= In;
		else
			Out <= RAM[address_out];
	end
end 

endmodule

