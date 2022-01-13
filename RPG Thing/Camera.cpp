#include "Camera.h"

Camera* CAMERA = NULL;

Camera* new_camera() {
	Camera* c = new Camera();

	return c;
}

void mount_camera(Camera* c) {
	CAMERA = c;
}

void unmount_camera() {
	delete CAMERA;
	CAMERA = NULL;
}
