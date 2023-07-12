#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/shader.h>
#include <engine/mesh.h>
#include <engine/draw.h>
#include <engine/input.h>
#include <engine/object.h>
#include <engine/graphics.h>
#include <engine/audio.h>
#include <engine/asset.h>
#include <engine/room.h>
#include <engine/camera.h>
#include <engine/ogg.h>
#include <engine/png.h>
#include <engine/texture.h>./
#include <engine/file.h>

#define DEFAULT_FRAGMENT_SHADER (char*)"assets/shaders/texture.fsh"
#define DEFAULT_VERTEX_SHADER (char*)"assets/shaders/transform.vsh"

#define DEFAULT_SFACTOR_BLENDMODE GL_SRC_ALPHA
#define DEFAULT_DFACTOR_BLENDMODE GL_ONE_MINUS_SRC_ALPHA

#define GLFW_VERSION_MAJOR 3
#define GLFW_VERSION_MINOR 3
#define GLFW_PROFILE GLFW_OPENGL_CORE_PROFILE

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Flappy bird"



