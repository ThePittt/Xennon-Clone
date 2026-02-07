#pragma once
#include "Renderer.h"
#include <string>
#include <glm/glm.hpp>

class UIElementText {
public:
	UIElementText(Renderer* renderer, const std::string& fontPath, const glm::vec2& position, int textSize);

	// Draw text at position
	//virtual void Update(float deltaTime);
	virtual void Draw();

	// Set text properties
	void SetColor(const glm::vec3& color) { textColor = color; }
	void SetCharacterSize(float width, float height);
	void AddScoreText(int scoreToAdd);
	void SetScoreText(int score);

	void SetTextToWrite(const std::string& text);
	bool isPendingKill = false;

	int scoreNumber = 000000;
private:
	Renderer* renderer;
	std::string textToWrite;
	std::string textLetters;
	int fontTextureHandle;

	float charWidth;   // Width of each character in pixels
	float charHeight;  // Height of each character in pixels
	float spacing;     // Space between characters

	int sheetWidth;    // Number of characters per row (typically 8)
	int sheetHeight;   // Number of rows (typically 12)

	glm::vec3 textColor;

	glm::vec2 textPosition;
	float scale;


	// Convert character to frame index in sprite sheet
	static int CharToFrame(char c);

	// Get UV coordinates for a specific character
	glm::vec4 GetCharUV(char c);
};