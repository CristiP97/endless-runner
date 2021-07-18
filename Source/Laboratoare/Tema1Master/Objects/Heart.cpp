#include "Heart.h"

#include <Core/Engine.h>

Mesh* Heart::CreateHeart(std::string name)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(-0.5f, 0.75f,  0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(-0.25f, 1, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(0, 0.75f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(0.25f, 1, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(0.5f, 0.75f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
	};

	std::vector<unsigned short> indices =
	{
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,5
	};

	//cube->SetDrawMode(GL_LINE_LOOP);
	Mesh* heart = new Mesh(name);

	heart->InitFromData(vertices, indices);
	return heart;
}