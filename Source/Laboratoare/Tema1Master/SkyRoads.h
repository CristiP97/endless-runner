#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>

#include <vector>
#include <string>

class SkyRoads : public SimpleScene
{
	public:
		SkyRoads();
		~SkyRoads();

		void Init() override;

		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

		struct Platform {
			float minX = -1;
			float maxX = 1;
			float minY = -1;
			float maxY = 1;
			float minZ = -1;
			float maxZ = 1;

			float centerX = 0;
			float centerY = 0;
			float centerZ = 0;

			bool createdBackup = false;
			bool isPlayerAbove = false;
			bool isHelper = false;
			bool appliedEffect = false;

			float laneOffset = 0;
			float scaleZ;

			int effect;
			int lane;
		};

		struct Player {
			//TODO: take into consideration the edges
			float posX = 0;
			float posY = 0;
			float posZ = 0;
			bool isDead = false;
			bool airborne = false;
		};

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void SetCameraPerspective();
		void RenderFuelBar();
		void RenderDeathCam(float deltaTimeSeconds);
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		// Custom made
		void GenerateNewPlatforms(Platform platform);
		void GenerateHelperPlatform(Platform parent);
		Platform SetPlatformLimits(Platform platform, bool helper, float offset);
		void RenderPlatforms();
		void MovePlatforms(float deltaTime);
		void RemovePlatforms();
		void RenderPlayer(glm::vec3 axis);
		void ManageSpeedBuff(float deltaTime);
		int CheckPlayerAbovePlatformXZ();
		void ApplyPlatformEffect(int index);
		void DebugPlatformInfo(Platform curPlat, char* specifier);
		void RenderHearts();
		void ResetPlayerPosition();
		void SideMovement(int dir, float deltaTime);
		int SetPlatformEffect();

		EngineComponents::Camera *camera = GetSceneCamera();
};
