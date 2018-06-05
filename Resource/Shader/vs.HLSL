cbuffer cbPerObject
{
    float4x4 gWorldViewProj;
}; 

struct VertexIn
{
    float3 PosL : POSITION;
    float3 Color : COLOR;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float3 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    // 转换到齐次剪裁空间    
   // vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
    vout.PosH = float4(vin.PosL, 1.0f);
    // 将顶点颜色直接传递到像素着色器    
	vout.Color = vin.Color;
    return vout;
}