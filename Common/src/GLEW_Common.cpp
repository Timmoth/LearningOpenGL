#pragma once

#include "../Headers/GLEW_Common.h"

int InitGLEW() {

	cout << "Initializing GLEW library" << endl;
	GLenum err = glewInit();

	//Check if there was an error returned
	if (GLEW_OK != err)
	{
		//Output the error
		cout << "glewInit failed" << glewGetErrorString(err) << endl;
		return 0;
	}

	cout << "Usign glew version: " << glewGetString(GLEW_VERSION) << endl;

	return 1;
}