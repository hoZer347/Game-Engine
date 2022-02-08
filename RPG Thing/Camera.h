#pragma once

#include <GLFW/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

struct Camera {
	vec3
		up = vec3(0, 1, 0),
		eye = vec3(0, 0, 0),
		look = vec3(0, 0, -5);

	mat3
		cam_ray = mat3(0);

	mat4
		roll = mat4(1),
		ptch = mat4(1),
		yaww = mat4(1),
		trns = mat4(1),
		rotn = mat4(1),
		mode = mat4(1),
		norm = mat4(1),
		view = mat4(1),
		proj = mat4(1),
		mvp = mat4(1);
};

// 
extern Camera* CAMERA;

// 
extern Camera* new_camera();

// 
extern void mount_camera(Camera*);

// 
extern void unmount_camera();
