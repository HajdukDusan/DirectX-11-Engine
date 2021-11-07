cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer Transform
{
    matrix transform;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;


    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;


    // Transform vertex position
    output.position = mul(input.position, transform);


    // BUMP MAP
    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Calculate the normal vector against the world matrix only and then normalize the final value.
    output.normal = mul(input.normal, (float3x3)transform);
    output.normal = mul(output.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);



    return output;
}