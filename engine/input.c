
#include <engine/input.h>

int key_press(GLFWwindow* window, int key) {
	return (glfwGetKey(window, key) == GLFW_PRESS);
}

int ord(char key) {
	int val = toupper(key);
	return (65 <= val) && (val <= 90) ? val : VK_UNKNOWN;
}



