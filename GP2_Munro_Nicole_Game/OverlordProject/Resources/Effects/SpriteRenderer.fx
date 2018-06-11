float4x4 gTransform : WorldViewProjection;
Texture2D gSpriteTexture;
float2 gTextureSize;

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = WRAP;
    AddressV = WRAP;
};

BlendState EnableBlending
{
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

DepthStencilState NoDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

RasterizerState BackCulling
{
    CullMode = BACK;
};

//SHADER STRUCTS
//**************
struct VS_DATA
{
    uint TextureId : TEXCOORD0;
    float4 TransformData : POSITION; //PosX, PosY, Depth (PosZ), Rotation
    float4 TransformData2 : POSITION1; //PivotX, PivotY, ScaleX, ScaleY
    float4 Color : COLOR;
};

struct GS_DATA
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD0;
};

//VERTEX SHADER
//*************
VS_DATA MainVS(VS_DATA input)
{
    return input;
}

//GEOMETRY SHADER
//***************
void CreateVertex(inout TriangleStream<GS_DATA> triStream, float3 pos, float4 col, float2 texCoord, float rotation, float2 rotCosSin, float2 offset, float2 pivotOffset)
{
    if (rotation != 0)
    {
		//Step 3.
		//Do rotation calculations

		//Transform to origin
		//Rotate
		//Retransform to initial position
        pos.x = (pivotOffset.x * rotCosSin.x) - (pivotOffset.y * rotCosSin.y);
        pos.y = (pivotOffset.y * rotCosSin.x) + (pivotOffset.x * rotCosSin.y);
    }
    else
    {
		//Step 2.
		//No rotation calculations (no need to do the rotation calculations if there is no rotation applied > redundant operations)
		//Just apply the pivot offset
        pos.xy += pivotOffset;

    }

	//Geometry Vertex Output
    GS_DATA geomData = (GS_DATA) 0;
    geomData.Position = mul(float4(pos, 1.0f), gTransform);
    geomData.Color = col;
    geomData.TexCoord = texCoord;
    triStream.Append(geomData);
}

[maxvertexcount(4)]
void MainGS(point VS_DATA vertex[1], inout TriangleStream<GS_DATA> triStream)
{
	//Given Data (Vertex Data)
    float3 position;
    position.x = vertex[0].TransformData.x; //Extract the position data from the VS_DATA vertex struct
    position.y = vertex[0].TransformData.y;
    position.z = vertex[0].TransformData.z;
    float rot;
    rot = vertex[0].TransformData.w;
    float2 offset;
    offset.x = vertex[0].TransformData2.x; //Extract the offset data from the VS_DATA vertex struct (initial X and Y position)
    offset.y = vertex[0].TransformData2.y;
    float rotation = vertex[0].TransformData.w; //Extract the rotation data from the VS_DATA vertex struct
    float2 pivot;
    pivot.x = vertex[0].TransformData2.x;
    pivot.y = vertex[0].TransformData2.y; //Extract the pivot data from the VS_DATA vertex struct
    float2 scale;
    scale.x = vertex[0].TransformData2.z; //Extract the scale data from the VS_DATA vertex struct
    scale.y = vertex[0].TransformData2.w;
    float2 texCoord = float2(0, 0); //Initial Texture Coordinate

    float2 rotCosSin;

    if (rot == 0)
    {
        rotCosSin = float2(0, 0);
    }
    else
    {
        rotCosSin.x = cos(rot);
        rotCosSin.y = sin(rot);
    }
	// LT----------RT //TringleStrip (LT > RT > LB, LB > RB > RT)
	// |          / |
	// |       /    |
	// |    /       |
	// | /          |
	// LB----------RB

    float2 scaledTextureSize = gTextureSize * scale;

	//VERTEX 1 [LT]
    float2 pivotOffset = (texCoord - pivot) * scaledTextureSize;
    CreateVertex(triStream, position, float4(1, 1, 1, 1), texCoord, rotation, rotCosSin, offset, pivotOffset); //Change the color data too!

	//VERTEX 2 [RT]
    pivotOffset = (float2(1, 0) - pivot) * scaledTextureSize;
    CreateVertex(triStream, position, float4(1, 1, 1, 1), float2(1, 0), rotation, rotCosSin, offset, pivotOffset); //Change the color data too!

	//VERTEX 3 [LB]
    pivotOffset = (float2(0, 1) - pivot) * scaledTextureSize;
    CreateVertex(triStream, position, float4(1, 1, 1, 1), float2(0, 1), rotation, rotCosSin, offset, pivotOffset); //Change the color data too!

	//VERTEX 4 [RB]
    pivotOffset = (float2(1, 1) - pivot) * scaledTextureSize;
    CreateVertex(triStream, position, float4(1, 1, 1, 1), float2(1, 1), rotation, rotCosSin, offset, pivotOffset); //Change the color data too!
}

//PIXEL SHADER
//************
float4 MainPS(GS_DATA input) : SV_TARGET {

    float4 sample = gSpriteTexture.Sample(samPoint, input.TexCoord) * input.Color;
    clip(sample.a < 0.1f ? -1 : 1);
	return sample;
}

// Default Technique
technique11 Default {

	pass p0 {
		SetRasterizerState(BackCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(NoDepth,0);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(CompileShader(gs_4_0, MainGS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}
