struct VertexOut
{
    float4 PosH : SV_POSITION;
    float3 Color : COLOR;
};

float4 PS(VertexOut pin) : SV_Target
{
    return float4(pin.Color, 1.0f);
}
