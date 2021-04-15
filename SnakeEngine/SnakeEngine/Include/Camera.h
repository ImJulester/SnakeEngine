#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/fast_square_root.hpp"

class Camera 
{
public :

	Camera();
	Camera(glm::vec3 position, glm::vec3 target,float width,float height, float fov);
	~Camera();

	glm::mat4 GetLookAt();
	glm::mat4 GetProjectionMatrix();


private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 target;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;


	glm::mat4 view;
	glm::mat4 projection;

	float fov;

	float width;
	float height;
};