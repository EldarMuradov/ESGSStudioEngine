Texture2D TextureColor: register(t0);
sampler TextureColorSampler: register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal: NORMAL0;
	float3 direction_to_camera: TEXCOORD1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	float4 m_camera_position;
	float4 m_light_position;
	float m_light_radius;
	float m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float4 color = TextureColor.Sample(TextureColorSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y));

	//AMBIENT LIGHT
	float ka = 1.5;
	float3 ia = float3(0.3, 0.3, 0.3);
	//float3 ia = float3(0.09, 0.082, 0.082);
	ia *= (color.rgb);

	float3 ambient_light = ka * ia;

	//DIFFUSE LIGHT
	float kd = 0.7;

	float amount_diffuse_light = dot(m_light_direction.xyz, input.normal);

	float3 id = float3(1, 1, 1);
	id *= (color.rgb);

	float3 diffuse_light = kd * id * amount_diffuse_light;

	//SPECULAR LIGHT
	float ks = 0.05;
	float3 is = float3(1.0, 1.0, 1.0);
	float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
	float shininess = 30.0;
	float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);

	float3 specular_light = ks * amount_specular_light * is;

	float3 final_light = ambient_light + diffuse_light + specular_light;

	return float4(final_light, 1.0);
}