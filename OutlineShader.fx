texture MainTex;
sampler2D MainMap = sampler_state
{
	Texture = (MainTex);
};

float4 Color;

float4 ps_main(float2 uv : TEXCOORD) : COLOR0
{
	float4 Texture = tex2D(MainMap, uv);

	float Alpha = Texture.a * 4.f;
	Alpha -= tex2D(MainMap, uv + float2(0.005f, 0)).a;
	Alpha -= tex2D(MainMap, uv + float2(-0.005f, 0)).a;
	Alpha -= tex2D(MainMap, uv + float2(0, 0.005f)).a;
	Alpha -= tex2D(MainMap, uv + float2(0, -0.005f)).a;

	if (Alpha != 0 && Texture.a == 0)
		Texture = Color;

	return Texture;
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