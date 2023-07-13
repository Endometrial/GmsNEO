#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <decoder/ogg.h>
#include <decoder/png.h>
#include <decoder/xml.h>

#include <baphomet/shader.h>
#include <baphomet/mesh.h>
#include <baphomet/draw.h>
#include <baphomet/input.h>
#include <baphomet/object.h>
#include <baphomet/window.h>
#include <baphomet/audio.h>
#include <baphomet/asset.h>
#include <baphomet/room.h>
#include <baphomet/camera.h>
#include <baphomet/texture.h>
#include <baphomet/file.h>


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



