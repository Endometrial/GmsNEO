#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/media.h>
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

#define DEFAULT_FRAGMENT_SHADER (char*)"assets/shaders/engine/texture.fsh"
#define DEFAULT_VERTEX_SHADER (char*)"assets/shaders/engine/transform.vsh"

#define GLFW_VERSION_MAJOR 3
#define GLFW_VERSION_MINOR 3
#define GLFW_PROFILE GLFW_OPENGL_CORE_PROFILE



