struct vsInput {
	float3 position : VS_POSITION;
	float3 color : VS_COLOR;
};

struct psInput {
	float4 position : SV_POSITION;
	float3 color : PS_COLOR;
};

cbuffer model : register(b0) {
	row_major float4x4 modelMatrix;
};

cbuffer view : register(b1) {
	row_major float4x4 viewMatrix;
};

cbuffer projection : register(b2) {
	row_major float4x4 projectionMatrix;
};

psInput vs_main(vsInput input) {
	psInput output;
	output.position.xyz = input.position;
	output.position.z *= 1;
	output.position.w = 1;
	output.position = mul(mul(mul(output.position, modelMatrix), viewMatrix), projectionMatrix);
	output.color = input.color;
	return output;
}