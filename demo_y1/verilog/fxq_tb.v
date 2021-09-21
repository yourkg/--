`include "fxq.v"
module inv_tb;
reg        [7:0]aa;
wire       [7:0]yy;
inv 	inv(
	.A(aa),
	.Y(yy)
	);

initial begin
		aa<=8'b01010000;
	#10	aa<=8'b11111111;
	#10	aa<=8'b00000000;
	#10	aa<=8'b01011001;
	#20	aa<=8'b01111111;
	#10	$stop;
end

initial begin
        $dumpfile("wave.vcd"); // 指定用作dumpfile的文件
		$dumpvars; // dump all vars
end
endmodule
