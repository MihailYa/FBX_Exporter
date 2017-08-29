#pragma once

struct SM_header
{
	float version;
	unsigned int NumOf_Vertices;
	unsigned int NumOf_Triangles;
	unsigned int NumOf_Materials;
	unsigned int NumOf_Textures;
};

struct SM_vertex
{
	XMFLOAT3 Position;
	XMFLOAT2 Tex0;
	XMFLOAT3 Normal;
};

struct SM_triangle
{
	unsigned int indices[3];
	int material_index;
};

struct SM_material
{
	XMFLOAT3 Emissive;
	XMFLOAT3 Ambient;
	XMFLOAT3 Diffuse;
	XMFLOAT3 Specular;
	XMFLOAT3 Reflection;

	float SpecularPower;
	float ReflectionFactor;
	float Transparency;
	float Shininess;
	
	// DIFFUSE_MAP, EMMISIVE_MAP, GLOSS_MAP, NORMAL_MAP, SPECULAR_MAP
	int Texture_index[5];
};

/*
	.static_mesh struct:
	{

		SM_header
		SM_vertex[NumOf_Vertices]
		SM_triangle[NumOf_Triangles]
		SM_material[NumOf_Materials]
		{
			unsigned int size_of_texture
			char Texture_file[size_of_texture]
		} * NumOf_Textures
	}
*/
