#pragma once
#include<vector>


struct float2
{
	float x{0.0f};
	float y{0.0f};
};

struct float3
{
	float x{0.0f};
	float y{0.0f};
	float z{0.0f};
};


struct ModelData
{
	std::vector<float3> vertices;
	std::vector<float2> uvs;
	std::vector<float3> normals;
	std::vector<unsigned> vertexIndexes;
	std::vector<unsigned> uvIndexes;
	std::vector<unsigned> normalIndexes;
};


#include <fstream>
#include <sstream>
#include <string>


// load obj and set value 
bool load_obj(const char* path, ModelData& out_data)
{
	if (path == nullptr)
		return false;

	std::ifstream file(path);
	if (!file.is_open())
		return false;

	for (std::string line; getline(file, line);)
	{
		std::istringstream in(line);
		std::string		type;
		in >> type;

		if (type == "v")
		{
			float3 vertex;
			in >> vertex.x >> vertex.y >> vertex.z;
			out_data.vertices.push_back(vertex);
		}
		else if (type == "vt")
		{
			float2 uv;
			in >> uv.x >> uv.y;
			out_data.uvs.push_back(uv);
		}
		else if (type == "vn")
		{
			float3 normal;
			in >> normal.x >> normal.y >> normal.z;
			out_data.normals.push_back(normal);
		}
		else if (type == "f")
		{
			int vertexIndex{ 0 }, uvIndex{ 0 }, normalIndex{ 0 };
			for (int i = 0; i < 3; i++)
			{
				in >> vertexIndex;
				in.ignore();
				in >> uvIndex;
				in.ignore();
				in >> normalIndex;

				out_data.vertexIndexes.push_back(vertexIndex);
				out_data.uvIndexes.push_back(uvIndex);
				out_data.normalIndexes.push_back(normalIndex);
			}
		}
	}

	return true;
}