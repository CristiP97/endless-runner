#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace SimpleCube
{
	Mesh* CreateCube(std::string name);
	Mesh* CreateActiveCube(std::string name);
	Mesh* CreateSpeedCube(std::string name);
	Mesh* CreateFuelBar(std::string name);
	Mesh* CreateFuelBackgroundBar(std::string name);
	Mesh* CreateFuelPlatform(std::string name);
	Mesh* CreateFuelLossPlatform(std::string name);
	Mesh* CreateDeathPlatform(std::string name);
}
