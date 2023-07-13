#include <baphomet/input.h>

int key_press(int key) {
	GLFWwindow* window = window_get_active_pointer();
	return (glfwGetKey(window, key) == GLFW_PRESS);
}

int ord(char key) {
	int val = toupper(key);
	return (65 <= val) && (val <= 90) ? val : VK_UNKNOWN;
}



