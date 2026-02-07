#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include <unordered_map>
#include <vector>

class Window;

class Renderer
{
public:

    Renderer(Window* window);
    ~Renderer();

    // Basic rendering
    void SetRenderDrawColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
    void SetRendererClear();
    void SetRendererPresent();

    // Texture management - returns a handle (just an int ID)
    int LoadTexture(const std::string& path, bool useColorKey);
    void UnloadTexture(int textureHandle);

    // Get texture info
    float GetTextureWidth(int textureHandle) const;
    float GetTextureHeight(int textureHandle) const;
    bool IsTextureValid(int textureHandle) const;

    // Drawing - actors just pass the handle
    void DrawTexture(
        int textureHandle,                      // Simple integer handle
        const glm::vec2& translation,
        const glm::vec2& scale,
        float rotation = 0.0f,
        const glm::vec4& srcRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 
        bool useSolidColor = false,
        const glm::vec4& color = glm::vec4(1.0f)
    );

    void OnWindowResize(int width, int height);
    SDL_GLContext GetContext() const { return glContext; }

private:
    // Internal texture data structure
    struct TextureData {
        GLuint glID;
        float width;
        float height;
        std::string path;
    };

    SDL_Window* sdlWindow;
    SDL_GLContext glContext;
    float clearColor[4];

    // OpenGL objects
    GLuint shaderProgram;
    GLuint VAO, VBO, EBO;
    glm::mat4 projection;

    // Texture storage - Renderer owns ALL textures
    std::vector<TextureData> textures;
    std::unordered_map<std::string, int> pathToHandle; // Prevent duplicates
    std::vector<int> freeSlots; // Reuse deleted texture slots

    // Initialization
    void InitOpenGL();
    void InitShaders();
    void InitQuad();

    GLuint CompileShader(const char* source, GLenum type);
    GLuint CreateShaderProgram(const char* vertexSrc, const char* fragmentSrc);
};