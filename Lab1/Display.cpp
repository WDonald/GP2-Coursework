#include "Display.h"


Display::Display()
{
	sdlWindow = nullptr;								// Initialise to generate null access violation for debugging. 
	screenWidth = 1024.0f;								// Initialise the value of screen width to 1024.  
	screenHeight = 768.0f;								// Initialise the value of screen height to 768.
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);					// Delete context.
	SDL_DestroyWindow(sdlWindow);						// Detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay()).
	SDL_Quit();											// Quit Game when called.
}

//Getters//
float Display::getWidth() { return screenWidth; }		// Returns the value stored in the variable ScreenWidth when called. 		
float Display::getHeight() { return screenHeight; }		// Returns the value stored in the variable ScreenHeight when called.

//Error Handeling//
void Display::returnError(std::string errorString)
{
	//Output//
	std::cout << errorString << std::endl;				
	std::cout << "press any  key to quit...";			
	
	//Inputs//
	int in;												
	std::cin >> in;
	SDL_Quit();											// Quit Game when called.
}

void Display::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow);						// Swap buffers.
}

void Display::clearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear colour and depth buffer - set colour to colour defined in glClearColor.
}

void Display::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING);						// Initalise everything.
	
	// Min No of bits used to diplay colour.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);			
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);			// Set up z-buffer.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);		// Set up double buffer.   

	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // Create window.

	//Error Check//
	if (sdlWindow == nullptr)
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	//Error Check//
	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	//Error Check//
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST);							// Enable z-buffering. 
	glEnable(GL_CULL_FACE);								// Dont draw faces that are not pointing at the camera.

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);				// create the colour with the RGB values R = 0, G = 1, B = 1 and an alpha of 1.  
}