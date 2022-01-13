#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

using namespace glm;

struct Mesh;
struct Camera;

class Renderer {
public:
	Renderer();
	~Renderer();
	void render(Mesh*);
	void update();
	void init();

	void create_shader(std::string, std::string);
	void create_shader(std::string, std::string, std::string);
	mat2x3 get_cam_ray();

	GLFWwindow* window = NULL;
	Camera* c = NULL;

private:
	GLuint vao = 0;
	GLuint shader_programme = 0, depth_shader = 0;
	GLuint depth_map = 0;
	GLuint _vtxs = 0, _inds = 0;
	GLuint mode=0, norm=0, view=0, proj=0, mvp=0;

	int window_w = 640, window_h = 640;
};

extern Renderer* create_renderer();
