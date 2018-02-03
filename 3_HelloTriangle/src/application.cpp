/*

GLEW is a cross platform open-source c/c++ extension loading library which provides run time mechanisims
for determining which OpenGL extensions are supported on the target platform.

This application demonstrates how to setup GLEW with GLFW and some basic usage

Introduction http://glew.sourceforge.net/index.html
Basic usage http://glew.sourceforge.net/basic.html

Bellow are the Visual studio Configuration properties needed to link GLFW and GLEW into our project
All Configurations All Platforms:

General
	Output Directory						$(SolutionDir)bin\$(Platform)\$(Configuration)
	Intermediate Directory					$(SolutionDir)bin\intermediates\$(Platform)\$(Configuration)

C++->General
	Additional Include Directories			$(SolutionDir)dependencies\GLFW\include;
											$(SolutionDir)dependencies\GLEW\include

Linker->General
	Additional Using Directories			$(SolutionDir)dependencies\GLFW\lib\$(Configuration)\$(PlatformTarget);
											$(SolutionDir)dependencies\GLEW\lib\$(Configuration)\$(PlatformTarget)

Linker->Input
	Additional Dependencies					opengl32.lib
											glfw3.lib

Build Events
	Post-Build Event						xcopy /y /d "$(SolutionDir)dependencies\GLEW\bin\$(Configuration)\$(PlatformTarget)\*.dll" "$(OutDir)"


Debug All Platforms
Linker->Input
	Additional Dependencies					glew32d.lib

Release All Platforms
Linker->Input
	Additional Dependencies					glew32.lib
*/

#include <iostream>

using namespace std;

int main() {

	cout << "Hello Triangles" << endl;


	cin.get();
	return 0;
}