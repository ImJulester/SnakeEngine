#include "Camera.h"
#include "GLFW/glfw3.h"

Camera::Camera()
{

}

Camera::Camera(glm::vec3 p, glm::vec3 t,float w,float h,float f)
{
	position = p;
	target = t;
	direction = glm::normalize(position - target);
	cameraRight = glm::fastNormalize(glm::cross(up, direction));
	cameraUp = glm::cross(direction, cameraRight);

	width = w;
	height = h;
	fov = f;

	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 10000.0f);
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetLookAt()
{
	//view = glm::lookAt(position, target, up);
	const float radius = 20.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projection;
}
