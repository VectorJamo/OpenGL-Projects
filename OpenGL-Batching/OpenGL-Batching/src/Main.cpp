#include "Window.h"
#include "Shader.h"
#include "Texture.h"

#define SIZE_OF_SPRITE sizeof(Vertex)*4
#define SIZE_OF_INDICES_PER_SPRITE sizeof(unsigned short) * 6

unsigned int num_sprites = 0;
unsigned int num_sprites_per_row = 0;
const float sprite_size = 0.05f;
const float gap_size = 0.025f;
const int sprites_per_row = (int)(2.0f / (sprite_size + gap_size));
float y_offset = 0.0f;

bool pressed = false;

struct Vertex
{
	float x, y, z;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void sendDataToGL(const unsigned int& vao, const unsigned int& vbo, const unsigned int& ibo)
{
	if (pressed)
	{
		pressed = false;
		float vertices[] =
		{
			-1.0f + (num_sprites_per_row * (sprite_size + gap_size)),               -(sprite_size / 2) + y_offset, 0.0f,
			-1.0f + (num_sprites_per_row * (sprite_size + gap_size)),				 (sprite_size / 2) + y_offset, 0.0f,
			-1.0f + (num_sprites_per_row * (sprite_size + gap_size)) + sprite_size,  (sprite_size / 2) + y_offset, 0.0f,
			-1.0f + (num_sprites_per_row * (sprite_size + gap_size)) + sprite_size, -(sprite_size / 2) + y_offset, 0.0f,
		};
		unsigned short indices[] =
		{
			0 + num_sprites * 4, 1 + num_sprites * 4, 2 + num_sprites * 4, 2 + num_sprites * 4, 0 + num_sprites * 4, 3 + num_sprites * 4
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, num_sprites * SIZE_OF_SPRITE, SIZE_OF_SPRITE, vertices);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, num_sprites * SIZE_OF_INDICES_PER_SPRITE, SIZE_OF_INDICES_PER_SPRITE, indices);

		num_sprites++;
		num_sprites_per_row++;
		std::cout << "Total Sprites: " << num_sprites << std::endl;
		std::cout << "Sprites in a Row: " << num_sprites_per_row << std::endl;

		if (num_sprites_per_row > sprites_per_row)
		{
			std::cout << "Added y offset!" << std::endl;
			num_sprites_per_row = 0;
			y_offset += sprite_size + gap_size;
		}
	}
}

int main()
{
	Window window(800, 600, "OpenGL Graphics");
	if (!window.init())
		std::cin.get();
	window.bgColor(0.4f, 0.3f, 0.6f, 1.0f);

	glfwSetKeyCallback(window.getWindowObject(), key_callback);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, SIZE_OF_SPRITE * 10000, 0, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SIZE_OF_INDICES_PER_SPRITE * 10000, 0, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Shaders
	Shader shader("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl");
	shader.Bind();
	glBindVertexArray(vao);
	while (!window.isClosed())
	{
		window.clear();

		sendDataToGL(vao, vbo, ibo);
		glDrawElements(GL_TRIANGLES, 6 + (num_sprites * 6), GL_UNSIGNED_SHORT, 0);

		window.processInput();
		window.swapBuffers();
	}
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT)
	{
		pressed = true;
	}
}