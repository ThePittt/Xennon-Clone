#include "pch.h"
#include "UIElementText.h"
#include <iostream>

UIElementText::UIElementText(Renderer* renderer, const std::string& fontPath, const glm::vec2& position, int textSize)
	: renderer(renderer),
	charWidth(8.0f),
	charHeight(8.0f),
	spacing(1.0f),
	sheetWidth(8),   // 8 characters per row
	sheetHeight(12), // 12 rows
	textColor(1.0f, 1.0f, 1.0f), textPosition(position.x,position.y), scale(textSize)
{
	fontTextureHandle = renderer->LoadTexture(fontPath, true);

	if (fontTextureHandle == -1) {
		std::cerr << "Failed to load font texture: " << fontPath << std::endl;
	}
}

void UIElementText::SetCharacterSize(float width, float height) {
	charWidth = width;
	charHeight = height;
}

void UIElementText::AddScoreText(int scoreToAdd)
{
	scoreNumber += scoreToAdd;
}

void UIElementText::SetScoreText(int score)
{
	scoreNumber = score;
}

void UIElementText::SetTextToWrite(const std::string& text)
{
	textLetters = text;
	textToWrite = textLetters + std::to_string(scoreNumber);
}
void UIElementText::Draw() {
	if (fontTextureHandle == -1) return;

	textToWrite = textLetters + std::to_string(scoreNumber);
	float x = textPosition.x;
	float y = textPosition.y;

	for (char c : textToWrite) {
		if (c == '\n') {
			// New line
			x = textPosition.x;
			y += (charHeight + spacing) * scale;
			continue;
		}

		if (c == ' ') {
			// Space - just advance position
			x += (charWidth + spacing) * scale;
			continue;
		}

		// Get UV coordinates for this character
		glm::vec4 uvCoords = GetCharUV(c);

		// Draw character
		renderer->DrawTexture(
			fontTextureHandle,
			glm::vec2(x, y),
			glm::vec2(charWidth * scale, charHeight * scale),
			0.0f,
			uvCoords
		);

		// Move to next character position
		x += (charWidth + spacing) * scale;
	}
}

glm::vec4 UIElementText::GetCharUV(char c) {
	int frameIndex = CharToFrame(c);

	// Calculate grid position
	int col = frameIndex % sheetWidth;
	int row = frameIndex / sheetWidth;

	// Get texture dimensions
	float texWidth = renderer->GetTextureWidth(fontTextureHandle);
	float texHeight = renderer->GetTextureHeight(fontTextureHandle);

	// Calculate character size in texture
	float charTexWidth = texWidth / sheetWidth;
	float charTexHeight = texHeight / sheetHeight;

	// Calculate UV coordinates
	float u1 = (col * charTexWidth) / texWidth;
	float v1 = (row * charTexHeight) / texHeight;
	float u2 = ((col + 1) * charTexWidth) / texWidth;
	float v2 = ((row + 1) * charTexHeight) / texHeight;

	return glm::vec4(u1, v1, u2, v2);
}

int UIElementText::CharToFrame(char c) {
	switch (c) {
		// Row 0
	case ' ': return 0;
	case '!': return 1;
	case '"': return 2;
	case '#': return 3;
	case '$': return 4;
	case '%': return 5;
	case '&': return 6;
	case '\'': return 7;

		// Row 1
	case '(': return 8;
	case ')': return 9;
	case '*': return 10;
	case '+': return 11;
	case ',': return 12;
	case '-': return 13;
	case '.': return 14;
	case '/': return 15;

		// Row 2 (Numbers)
	case '0': return 16;
	case '1': return 17;
	case '2': return 18;
	case '3': return 19;
	case '4': return 20;
	case '5': return 21;
	case '6': return 22;
	case '7': return 23;

		// Row 3
	case '8': return 24;
	case '9': return 25;
	case ':': return 26;
	case ';': return 27;
	case '<': return 28;
	case '=': return 29;
	case '>': return 30;
	case '?': return 31;

		// Row 4
	case '@': return 32;
	case 'A': return 33;
	case 'B': return 34;
	case 'C': return 35;
	case 'D': return 36;
	case 'E': return 37;
	case 'F': return 38;
	case 'G': return 39;

		// Row 5
	case 'H': return 40;
	case 'I': return 41;
	case 'J': return 42;
	case 'K': return 43;
	case 'L': return 44;
	case 'M': return 45;
	case 'N': return 46;
	case 'O': return 47;

		// Row 6
	case 'P': return 48;
	case 'Q': return 49;
	case 'R': return 50;
	case 'S': return 51;
	case 'T': return 52;
	case 'U': return 53;
	case 'V': return 54;
	case 'W': return 55;

		// Row 7
	case 'X': return 56;
	case 'Y': return 57;
	case 'Z': return 58;
	case '[': return 59;
	case '\\': return 60;
	case ']': return 61;
	case '^': return 62;
	case '_': return 63;

		// Row 8
	case '`': return 64;
	case 'a': return 65;
	case 'b': return 66;
	case 'c': return 67;
	case 'd': return 68;
	case 'e': return 69;
	case 'f': return 70;
	case 'g': return 71;

		// Row 9
	case 'h': return 72;
	case 'i': return 73;
	case 'j': return 74;
	case 'k': return 75;
	case 'l': return 76;
	case 'm': return 77;
	case 'n': return 78;
	case 'o': return 79;

		// Row 10
	case 'p': return 80;
	case 'q': return 81;
	case 'r': return 82;
	case 's': return 83;
	case 't': return 84;
	case 'u': return 85;
	case 'v': return 86;
	case 'w': return 87;

		// Row 11
	case 'x': return 88;
	case 'y': return 89;
	case 'z': return 90;
	case '{': return 91;
	case '|': return 92;
	case '}': return 93;

	default: return 0; // Space for unknown characters
	}
}
