float4 FireColor[3][8] =
{
	{
		float4(1,1,1,1),
		float4(1,1,0.7411,1),
		float4(1,0.9686, 0.6117,1),
		float4(1, 0.9058, 0.4823, 1),
		float4(1,0.7098, 0.2235, 1),
		float4(0.9686, 0.5803, 0.1294, 1),
		float4(0.8705, 0.3529, 0, 1),
		float4(0.7411,0.2235,0,1)
	},
	{
		float4(1,1,1,1),
		float4(0.9648,0.8671,1,1),
		float4(0.8671,0.7098, 1,1),
		float4(0.7764, 0.5490, 1, 1),
		float4(0.6117,0.4196, 1, 1),
		float4(0.3882, 0.3215, 0.9686, 1),
		float4(0.3215, 0.2588, 0.9686, 1),
		float4(0.2588,0.2235,0.9372,1)
	},
	{
		float4(0.1882,0.1254,0.4705,1),
		float4(0.2823, 0.2196, 0.5647, 1),
		float4(0.3764, 0.3137, 0.6588, 1),
		float4(0.5019,0.4392, 0.7843, 1),
		float4(0.6274, 0.5647, 0.9098, 1),
		float4(0.6588,0.5960, 0.9411,1),
		float4(0.7215,0.6588,0.9725,1),
		float4(0.7843,0.7215,0.9725,1)
	}
};

texture FireTexture;
sampler2D FireMap = sampler_state
{
	Texture = (FireTexture);
};

int Time;
int Pallete;

float4 ps_main(float2 uv : TEXCOORD) : COLOR0
{
	float4 Fire = tex2D(FireMap, uv);
	float4 Result = float4(0, 0, 0, 1);

	if (Pallete != 2)
	{
		Result = FireColor[Pallete][(int)((Fire.r + Fire.g + Fire.b) * 2.34 + Time) % 8] * Fire.a;
	}
	else
	{
		Result = FireColor[Pallete][(int)((Fire.r + Fire.g + Fire.b) * 2.34) % 8] * Fire.a;
	}

	return Result;
}

technique
{
	pass p0
	{
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		PixelShader = compile ps_2_0 ps_main();
	}
};