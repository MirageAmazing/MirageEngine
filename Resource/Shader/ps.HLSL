struct VertexOut
{
    float4 PosH : SV_POSITION;
    float3 Color : COLOR;
};

#define cMult 0.0001002707309736288
#define aSubtract 0.2727272727272727

float4 randGrieu(float4 t)
{
    float a = t.x + t.z * cMult + aSubtract - floor(t.x);
    a *= a;
    float b = t.y + a;
    b -= floor(b);
    float c = t.z + b;
    c -= floor(c);
    float d = c;
    a += c * cMult + aSubtract - floor(a);
    a *= a;
    b += a;
    b -= floor(b);
    c += b;
    c -= floor(c);
    return float4(a, b, c, d);
}

float4 PS(VertexOut pin) : SV_Target
{
    return (float4(pin.Color.r, (pin.Color.g), pin.Color.b, 1.0f));
}
