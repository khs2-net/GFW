struct VSOUT {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};
SamplerState samLinear		: register(s0);
Texture2D texAlbed			: register(t0);
float4 main(VSOUT inp) : SV_TARGET
{
	float4 col = texAlbed.Sample(samLinear,inp.tex);
	float tempPixel = ( col.r + col.g + col.b ) * 0.3333f;
	col = tempPixel;
	return col;
}
