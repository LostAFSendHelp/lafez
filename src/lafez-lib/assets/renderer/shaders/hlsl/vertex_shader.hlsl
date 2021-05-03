struct vsInput {
	float3 position : VS_POSITION;
	float3 color : VS_COLOR;
};

struct psInput {
	float4 position : SV_POSITION;
	float3 color : PS_COLOR;
};

psInput vs_main(vsInput input) {
	psInput output;
	output.position.xyz = input.position;
	output.position.w = 1;
	output.color = input.color;
	return output;
}