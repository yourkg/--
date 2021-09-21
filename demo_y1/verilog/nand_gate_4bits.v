//����ţ�
`timescale 1ns/10ps
module nand_gate_4bits(
	A,
	B,
	Y
	);
input[3:0]	A;
input[3:0]	B;
output[3:0]	Y;

assign	Y=~(A&B);

endmodule

//---------testbench of nand_gate----
module nand_gate_4bits_tb;
reg[3:0]	aa,bb;
wire[3:0]	yy;
nand_gate_4bits nand_gate_4bits(
		.A(aa),
		.B(bb),
		.Y(yy)
		);
initial begin
		aa<=4'b0000;bb<=4'b1111;
	#10	aa<=4'b0010;bb<=4'b0110;
	#10	aa<=4'b0111;bb<=4'b0100;
	#10	aa<=4'b0000;bb<=4'b1110;
	#10	$stop;
end

endmodule