#include "pch.h"
#include "Renderer.h"
#include "Window.h"
#include <iostream>

// Vertex Shader - transforms vertices using translation, rotation, scale
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;      // Vertice Position (0..1)
layout (location = 1) in vec2 aTexCoord; // UV Coordinates 

out vec2 TexCoord;

uniform mat4 model;      // Identity Matrix
uniform mat4 projection; // Projection Matrix

void main()
{
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

// Fragment Shader - samples texture and applies color tint
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D image; 

uniform bool useSolidColor; 
uniform vec4 solidColor;

void main()
{
	vec4 texColor = texture(image, TexCoord);
	if (useSolidColor) 
	{
		FragColor = vec4(solidColor.rgb, texColor.a * solidColor.a);
	}
	else 
	{
		FragColor = texColor;
	}
    
}
)";

Renderer::Renderer(Window* window)
	: sdlWindow(window->GetNativeWindow()),
	clearColor{ 0.0f, 0.0f, 0.0f, 1.0f }
{
	InitOpenGL();
	InitShaders();
	InitQuad();

	// Set initial projection matrix
	int width, height;
	SDL_GetWindowSize(sdlWindow, &width, &height);
	OnWindowResize(width, height);
}

Renderer::~Renderer()
{
	for (auto& tex : textures) {
		if (tex.glID != 0) {
			glDeleteTextures(1, &tex.glID);
		}
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	SDL_GL_DestroyContext(glContext);
}

void Renderer::InitOpenGL()
{
	// Set OpenGL attributes BEFORE creating context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	

	// Create OpenGL context
	glContext = SDL_GL_CreateContext(sdlWindow);
	if (!glContext) {
		std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return;
	}

	// Initialize GLAD - MUST be after context creation
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Enable VSync
	SDL_GL_SetSwapInterval(1);

	// Set viewport
	int width, height;
	SDL_GetWindowSize(sdlWindow, &width, &height);
	glViewport(0, 0, width, height);

	// Enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "OpenGL initialized successfully" << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Renderer::InitShaders()
{
	shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	// Set texture sampler to use texture unit 0
	glUseProgram(shaderProgram);
	GLint textureLoc = glGetUniformLocation(shaderProgram, "texture1");
	glUniform1i(textureLoc, 0);
}

void Renderer::InitQuad()
{
	// Unit quad vertices (0,0 to 1,1) with texture coordinates
	float vertices[] = {
		// Position    // TexCoord
		0.0f, 1.0f,    0.0f, 1.0f,  // Top-left
		1.0f, 0.0f,    1.0f, 0.0f,  // Bottom-right
		0.0f, 0.0f,    0.0f, 0.0f,  // Bottom-left
		1.0f, 1.0f,    1.0f, 1.0f   // Top-right
	};

	unsigned int indices[] = {
		0, 1, 2,  // First triangle
		0, 3, 1   // Second triangle
	};

	// Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and setup VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// Generate and setup EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture coordinate attribute 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindVertexArray(0);
}

GLuint Renderer::CompileShader(const char* source, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
	}

	return shader;
}

GLuint Renderer::CreateShaderProgram(const char* vertexSrc, const char* fragmentSrc)
{
	GLuint vertexShader = CompileShader(vertexSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Check for linking errors
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
	}

	// Clean up shaders (they're linked into program now)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}


int Renderer::LoadTexture(const std::string& path, bool useColorKey)
{

	// Check if already loaded (duplication)
	auto it = pathToHandle.find(path);
	if (it != pathToHandle.end()) {
		std::cout << "Texture already loaded: " << path << std::endl;
		return it->second;
	}

	// Create a surface from the file
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (!surface) {
		std::cerr << "Failed to load: " << path << std::endl;
		return -1;
	}

	// Convert texture to RGBA
	SDL_Surface* rgbaSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
	// Destroy original surface
	SDL_DestroySurface(surface);

	if (!rgbaSurface) {
		std::cerr << "Failed to convert surface format" << std::endl;
		return -1;
	}
	if(useColorKey)
	{
		// Process Pixels
		Uint32* pixels = (Uint32*)rgbaSurface->pixels;
		int pixelCount = rgbaSurface->w * rgbaSurface->h;

		// Change target color pixels to transparent
		Uint32 targetColor = SDL_MapSurfaceRGB(rgbaSurface, 255, 0, 255);
		Uint32 transparentColor = SDL_MapSurfaceRGBA(rgbaSurface, 0, 0, 0, 0);

		for (int i = 0; i < pixelCount; i++) {
			if (pixels[i] == targetColor) {
				pixels[i] = transparentColor;
			}
		}
	}
	
	// Create OpenGL texture
	GLuint glID;
	glGenTextures(1, &glID);
	glBindTexture(GL_TEXTURE_2D, glID);

	// Set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Upload data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgbaSurface->w, rgbaSurface->h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaSurface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Create texture data
	TextureData texData;
	texData.glID = glID;
	texData.width = static_cast<float>(rgbaSurface->w);
	texData.height = static_cast<float>(rgbaSurface->h);
	texData.path = path;

	SDL_DestroySurface(rgbaSurface);

	// Store in vector and return handle
	int handle;
	if (!freeSlots.empty()) {
		// Reuse a free slot
		handle = freeSlots.back();
		freeSlots.pop_back();
		textures[handle] = texData;
	}
	else {
		// Add new slot
		handle = textures.size();
		textures.push_back(texData);
	}

	pathToHandle[path] = handle;

	std::cout << "Loaded: " << path << " (handle: " << handle << ")" << std::endl;
	return handle;
}

void Renderer::UnloadTexture(int handle)
{
	if (handle < 0 || handle >= textures.size()) return;

	TextureData& tex = textures[handle];
	if (tex.glID != 0) {
		glDeleteTextures(1, &tex.glID);
		pathToHandle.erase(tex.path);
		tex = TextureData{}; // Clear data
		freeSlots.push_back(handle); // Mark as reusable
	}
}

float Renderer::GetTextureWidth(int handle) const
{
	if (handle < 0 || handle >= textures.size()) return 0.0f;
	return textures[handle].width;
}

float Renderer::GetTextureHeight(int handle) const
{
	if (handle < 0 || handle >= textures.size()) return 0.0f;
	return textures[handle].height;
}

bool Renderer::IsTextureValid(int handle) const
{
	return handle >= 0 && handle < textures.size() && textures[handle].glID != 0;
}

void Renderer::DrawTexture(int textureHandle, const glm::vec2& translation,
	const glm::vec2& scale, float rotation,
	const glm::vec4& srcRect,
	bool useSolidColor,         
	const glm::vec4& color)
{
	if (!IsTextureValid(textureHandle)) return;

	glUseProgram(shaderProgram);

	glm::mat4 model = glm::mat4(1.0f); // Create Identity Matrix

	// Translation
	model = glm::translate(model, glm::vec3(translation, 0.0f));

	// Move origin to sprite center
	model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	// Rotation
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	// Return to original Position
	model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	// Scale
	model = glm::scale(model, glm::vec3(scale, 1.0f));


	// Check if uses Solid Color
	GLint useSolidLoc = glGetUniformLocation(shaderProgram, "useSolidColor");
	glUniform1i(useSolidLoc, useSolidColor); // 1 for true, 0 for false

	// Send the Solid Color 
	if (useSolidColor) {
		GLint colorLoc = glGetUniformLocation(shaderProgram, "solidColor");
		glUniform4f(colorLoc, color.r, color.g, color.b, color.a);
	}

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

	float vertices[] = {
		0.0f, 1.0f, srcRect.x, srcRect.w,
		1.0f, 0.0f, srcRect.z, srcRect.y,
		0.0f, 0.0f, srcRect.x, srcRect.y,
		1.0f, 1.0f, srcRect.z, srcRect.w
	};

	// Rebind vbo because of vertice change
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Activate textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[textureHandle].glID);

	// Draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::SetRenderDrawColor(float r, float g, float b, float a)
{
	clearColor[0] = r;
	clearColor[1] = g;
	clearColor[2] = b;
	clearColor[3] = a;
}

void Renderer::SetRendererClear()
{
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetRendererPresent()
{
	SDL_GL_SwapWindow(sdlWindow);
}

void Renderer::OnWindowResize(int width, int height)
{
	glViewport(0, 0, width, height);

	// Update projection matrix for new window size
	projection = glm::ortho(0.0f, static_cast<float>(width),
		static_cast<float>(height), 0.0f,
		-1.0f, 1.0f);

	glUseProgram(shaderProgram);
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
}