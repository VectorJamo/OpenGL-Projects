#include "Window.h"

Window::Window(int width, int height, const char* title)
	:_width(width), _height(height), _title(title), _window(nullptr)
{
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "|| FATAL ERROR: || Failed to init GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);

	if (_window == nullptr)
	{
		std::cout << "|| FATAL ERROR: || Failed to init GLFW Window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSetWindowSizeCallback(_window, window_size_callback);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "|| FATAL ERROR: || Failed to init GLEW" << std::endl;
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::swapBuffers() const
{
	glfwSwapBuffers(_window);
}
void Window::processInput()
{
	glfwPollEvents();

	// Process Keyboard Inputs
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	// Get new window size ( if window was resized )
	glfwGetWindowSize(_window, &_width, &_height);

}
bool Window::isClosed() const
{
	return glfwWindowShouldClose(_window);
}

void Window::bgColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}