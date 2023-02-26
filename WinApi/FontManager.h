#pragma once

//°úÁ¦
class FontManager
{
public:
	void drawText(HDC hdc, int destX, int destY, char* fontName, char* fontSize,
		int fontWeight, char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, char* fontSize,
		int fontWeight, LPCWSTR printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, char* fontSize,
		int fontWeight, LPCWSTR* printStringArr, int length, COLORREF color);

	
	FontManager();
	~FontManager();
};

