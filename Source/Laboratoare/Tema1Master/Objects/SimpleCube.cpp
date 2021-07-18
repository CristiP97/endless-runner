#include "SimpleCube.h"

#include <Core/Engine.h>

Mesh* SimpleCube::CreateCube(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 1, 1), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 1, 1), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 1, 1), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 1), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 1, 1), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,		
		1, 3, 2,
		2, 3, 7,		
		2, 7, 6,
		1, 7, 3,		
		1, 5, 7,
		6, 7, 4,		
		7, 5, 4,
		0, 4, 1,		
		1, 4, 5,
		2, 6, 4,		
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateActiveCube(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 1), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 0, 1), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0, 1), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0, 1), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 0, 1), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateSpeedCube(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0.7, 0), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0.7, 0), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0.7, 0), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 0.7, 0), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0.7, 0), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0.7, 0), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 0.7, 0), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 0.7, 0), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateFuelBar(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0, 0, 1), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 0, 1), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 0, 1), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateFuelBackgroundBar(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 0, 0.55), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0, 0, 0.55), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0, 0, 0.55), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 0, 0.55), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 0.55), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 0, 0.55), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0, 0, 0.55), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 0.55), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateFuelPlatform(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 1, 0), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateFuelLossPlatform(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 1, 0), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 0), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 1, 0), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* SimpleCube::CreateDeathPlatform(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.2)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 0), glm::vec3(0.9, 0.4, 0.2)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.3, 0.7)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0, 0), glm::vec3(0.3, 0.5, 0.4)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0, 0), glm::vec3(0.5, 0.2, 0.9)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.0, 0.7)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 0, 0), glm::vec3(0.1, 0.5, 0.8)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}