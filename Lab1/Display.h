#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();													// Constructor.
	~Display();													// Desrtuctor. 
	
	void initDisplay();											// Initialisation of the display.
	void swapBuffer();											// Swap the buffer when called.
	void clearDisplay(float r, float g, float b, float a);		// Clears the display when called.

	float getWidth();											// Getter for the screen width.
	float getHeight();											// Getter for the screen heigh.

private:

	void returnError(std::string errorString);					// Error handeling.
	
	SDL_GLContext glContext;									// Global variable to hold the context.
	SDL_Window* sdlWindow;										// Holds pointer to out window.
	
	float screenWidth;											// Holds the value of the screen width.  
	float screenHeight;											// Holds the value of the screen height.   
};

