#pragma once
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>

using namespace std;

int InitGLFW();

GLFWwindow* CreateGLFWwindow(string title, int width, int height);