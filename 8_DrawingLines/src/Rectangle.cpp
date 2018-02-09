#pragma once
#include "../headers/Rectangle.h"

Rectangle::Rectangle(float x, float y, float width, float height, float thickness, unsigned int ShaderProgram) {
	ShaderProgramID = ShaderProgram;

	float halfWidth = width / 2;
	float halfHeight = height / 2;

	float x1 = x - halfWidth - thickness;
	float y1 = y - halfHeight - thickness;

	float x2 = x + halfWidth + thickness;
	float y2 = y + halfHeight + thickness;

	lines.push_back(Line(x1 + thickness, y1, x2, y1, thickness, ShaderProgram));
	lines.push_back(Line(x2, y1 + thickness, x2, y2 , thickness, ShaderProgram));
	lines.push_back(Line(x2 - thickness, y2, x1, y2, thickness, ShaderProgram));
	lines.push_back(Line(x1, y2 - thickness, x1, y1, thickness, ShaderProgram));
}

void Rectangle::Render() {
	for (std::vector<Line>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		(*it).Render();
	}
}