`timescale 1ns/10ps //应该写在tb里，其余几个器件，同
module inv(
	A,
	Y
	);

input[7:0]	A;
output[7:0]	Y;

assign	Y=~A;

endmodule
