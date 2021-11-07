cbuffer LightBuffer
{
    float4 diffuseColor;
    float3 lightDirection;
    float NormalMapEffect;
    float4 specularColor;
    float specularPower;

    //float3 padding;
};

cbuffer ColorBuffer
{
    float4 objectColor;
};

struct PixelInputType
{
    float4 position         :  SV_POSITION;
    float3 normal           :  NORMAL;
};


float4 main(PixelInputType input) : SV_TARGET
{
    float3 lightDir;
    float lightIntensity;
    float4 color;

    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel based on the bump map normal value.
    lightIntensity = saturate(dot(input.normal, lightDir));


    // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
    color = saturate(diffuseColor * lightIntensity);

    // Combine the final bump light color with the texture color.
    color = color * objectColor;



    // SPECULAR
    if (lightIntensity > 0.0f) {
        color = saturate(color);
    }


    // Disable transparency
    color.w = 1.0f;

    return color;
}