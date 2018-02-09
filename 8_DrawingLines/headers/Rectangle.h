#pragma once
#include "Line.h"
#include <vector>

using namespace std;

class Rectangle {
private:
	unsigned int ShaderProgramID;
	vector<Line> lines;

public:

	Rectangle(float x, float y, float width, float height, float thickness, unsigned int ShaderProgram);
	void Render();

};