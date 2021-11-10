#include "Tracer.h"
#include "ColorBuffer.h"
#include "Buffer.h"
#include "Scene.h"
#include <iostream>

void Tracer::Trace(Buffer* buffer, Scene* scene, Camera* camera, const std::string& messages)
{
	float aspectRatio = (buffer->width / (float)buffer->height);
	float invSamples = 1.0f / samples;

	for (int y = 0; y < buffer->height; y++) {
		for (int x = 0; x < buffer->width; x++) {
			glm::vec3 color = { 0,0,0 };

			for (int sample = 0; sample < samples; sample++) {

				glm::vec2 viewport = camera->ScreenToViewport({ x + random01(), y + random01() });
				viewport.y = 1 - (viewport.y);
				ray_t ray = camera->ViewportToRay(viewport);

				raycastHit_t hit;
				color += scene->Trace(ray, 0.001f, FLT_MAX, hit,depth);
			}
			buffer->Add(x, y, color);
		}
		system("CLS");
		std::cout << messages << std::endl;
		std::cout << y << std::endl;
	}
}
