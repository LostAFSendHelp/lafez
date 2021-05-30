struct psInput {
	float4 position : SV_POSITION;
	float3 color : PS_COLOR;
};

float4 ps_main(psInput input) : SV_TARGET {
	float4 output = { .0f, .0f, .0f, 1.0f };
	output.xyz = input.color;
	output.w = 1;
	return output;
};
