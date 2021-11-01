#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov, const glm::ivec2& screenSize)
{
	this->screenSize = screenSize;
	this->aspectRatio = (screenSize.x / (float)screenSize.y);

	float theta = glm::radians(fov);
	float h = tan(theta * 0.5f);

	viewportHeight = h * 2.0f;
	viewportWidth = viewportHeight * aspectRatio;

	Set(eye, lookAt, up, fov);
}

void Camera::Set(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov)
{
	this->eye = eye;

	forward = glm::normalize(lookAt - this->eye);
	right = glm::normalize(glm::cross(forward, up));
	this->up = glm::cross(right, forward);

	horizontal = viewportWidth * right;
	vertical = viewportHeight * this->up;

	lowerLeft = this->eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward;
}

glm::vec2 Camera::ScreenToViewport(const glm::vec2& screen)
{
	glm::vec2 viewport{ 0, 0 };

	viewport.x = screen.x / (float)screenSize.x;
	viewport.y = screen.y / (float)screenSize.y;


	return viewport;
}

ray_t Camera::ViewportToRay(const glm::vec2& viewport)
{
	//glm::vec3 random = 
	ray_t ray;
	
	ray.origin = eye;
	ray.direction = lowerLeft + (viewport.x * horizontal) + (viewport.y * vertical) - eye;

	return ray;
}
