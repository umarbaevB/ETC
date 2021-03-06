`timescale 1 ns/ 10 ps

module lab4part13(clk, S, R, ser_input, out);
input clk, S, R, ser_input;
reg[7:0] par_output;
output reg[7:0] out;
reg[3:0] count = 0;

always @ (posedge clk) begin 
	if (R) 
		 par_output <= 8'b0;
	else
	begin
		if(S)
		begin
		par_output <= {ser_input, par_output[7:1]};
		count <= count + 1;
		end
	end
	if(count == 8)
	begin
		out <= par_output;
		count <= 0;
	end	
end 


endmodule

