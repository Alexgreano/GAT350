#pragma once
#include "Types.h"
#include "ColorBuffer.h"
#include "Buffer.h"
#include "Camera.h"

class Scene;
class Camera;
struct Buffer;

class Tracer {
public:
	void Trace(Buffer* buffer, Scene* scene, Camera* camera, const std::string& messages);
public:
	int samples = 1;
	int depth = 50;
};