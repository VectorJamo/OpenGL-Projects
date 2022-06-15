#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Window
{
private:
	int _width, _height;
	const char* _title;

	GLFWwindow* _window;

public:
	Window(int width, int height, const char* title);
	~Window();
	bool init();
	void clear() const;
	void swapBuffers() const;
	void processInput();
	bool isClosed() const;
	void bgColor(float r, float g, float b, float a) const;

	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }
	inline GLFWwindow* getWindowObject() { return _window; }
};

void window_size_callback(GLFWwindow* window, int width, int height);
