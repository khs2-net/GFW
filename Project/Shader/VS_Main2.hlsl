cbuffer ConstantBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}
struct VSIN {
	float4 pos : POSITION;
	float2 tex: TEXCOORD0;
	float4 col : COLOR;
};
struct VSOUT {
	float4 pos : SV_POSITION;
	float2 tex: TEXCOORD0;
	float4 col : COLOR;
};
VSOUT main( VSIN inp){
	VSOUT outp = (VSOUT) 0;
	outp.pos = inp.pos;
	outp.col = inp.col;
	outp.tex = inp.tex;
	return outp;
}