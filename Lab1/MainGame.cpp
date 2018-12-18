#include "MainGame.h"
#include "GameCamera.h"
#include <iostream>
#include <string>

extern Transform transform;						// Transform used to move the ship. 

//Constructor//
MainGame::MainGame()
{
	_gameState = GameState::PLAY;				// Set the game state to play.
	Display* _gameDisplay = new Display();		// New display.
    Mesh* meshRing();							// Create meshRing.
	Mesh* meshShip();							// Create meshShip.
	Mesh* meshRing2();							// Create meshRing2.
	
	Texture* texture();							// Create texture.
	Shader* shader();							// Create shader.
}

//Destructor//
MainGame::~MainGame()
{
}


void MainGame::run()
{
	score = 0;									// Set the score to 0.
	r1Direct = 10;								// Set r1Direct to 10.
	r2Direct = -10;								// Set r2Direct to -10.
	transform.setTransform();					// Set the transform used by the ship to initial requierd values.
	initSystems();								// Call initSystems.
	gameLoop();									// Call gameLoop.
	
}

//Check if two objects are colliding// 
bool MainGame::checkCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad, int ringNo)
{
	float distSq = (
						(m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + 
						(m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + 
						(m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z)
					   );						// Use the equation to set the value of distSq.

	if (distSq < (m1Rad * m2Rad) * (m1Rad * m2Rad))	// If the square of the two radii is less than distSq.
	{
		if (ringNo == 1)						// If ringNo is 1.
		{
			score++;							// Increase score by 1.
			cout << "Score: " << score << endl;	// Output to console. 
			transform2 = Transform(glm::vec3(transform2.GetPos()->x + r1Direct, -10, 500), glm::vec3(90, 180, 0), glm::vec3(0.2, 0.2, 0.2)); // Set the transform of the first ring to a new position.
		}

		if (ringNo == 2)						// If ringNo is 2.
		{
			score += 2;							// Increase score by 2.
			cout << "Score: " << score << endl; // Output to console.
			transform3 = Transform(glm::vec3(transform3.GetPos()->x + r2Direct, -10, 500), glm::vec3(90, 180, 0), glm::vec3(0.03, 0.03, 0.03)); // Set the transform of the second ring to a new position.
		}
		
		return true;							// Return true. 
	}

	return false;								// If the condition for the first if statement was not met then return false.
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay();					// Initialise the game display.

	//load the model and textures 
	meshShip.loadModel("..\\res\\Ship.obj");	// Load the ship model.
	texture.init("..\\res\\Ship.png");			// Load the ship texture.
	shader.init("..\\res\\shader");				// New shader.
	
	//load the model and textures for the first ring
	meshRing.loadModel("..\\res\\Ring.obj");	// Load the first ring model.
	texture2.init("..\\res\\Scifi_Hex_Wall.jpg"); // Load the first ring texture.
	shader.init("..\\res\\shader");				// New shader.

	//load the model and textures for the second ring
	meshRing2.loadModel("..\\res\\Ring2.obj");	// Load the second ring model.
	texture3.init("..\\res\\RingTexture2.png"); // Load the second ring texture.
	shader.init("..\\res\\shader");				// New shader.

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f); // Initialise the camera.
}

//Game loop//
void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)		// Loop until the game state changes to EXIT. 
	{
		processInput();							// Call ProcessInput.
		drawGame();								// Call drawGame.
		 
		checkCollision(*meshShip.SpherePos(), *meshShip.sphereRadius(), *meshRing.SpherePos(), *meshRing.sphereRadius(), 1);	// Check if the ship and the first ring are colliding.
		
		checkCollision(*meshShip.SpherePos(), *meshShip.sphereRadius(), *meshRing2.SpherePos(), *meshRing2.sphereRadius(), 2);	// Check if the ship and the second ring are colliding.
		
		
		if (transform2.GetPos()-> z < -10)		// If the Z position of transform2 is less than - 10.
		{
			transform2 = Transform(glm::vec3(transform2.GetPos()->x + r1Direct, -10, 500), glm::vec3(90, 180, 0), glm::vec3(0.2, 0.2, 0.2)); // Set transform2 to a new position.
		}
		else
		{
			transform2 = Transform(glm::vec3(transform2.GetPos()->x, -10, transform2.GetPos()->z - 0.5), glm::vec3(90, 180, 0), glm::vec3(0.2, 0.2, 0.2)); // move transform2 by -0.5 each loop.
		}

		if (transform3.GetPos()->z < -10)		// If the Z position of transform3 is less than - 10.
		{
			transform3 = Transform(glm::vec3(transform3.GetPos()->x + r2Direct, -10, 500), glm::vec3(90, 90, 0), glm::vec3(0.03, 0.03, 0.03)); // Set transform3 to a new position.
		}
		else
		{
			transform3 = Transform(glm::vec3(transform3.GetPos()->x, -10, transform3.GetPos()->z - 1), glm::vec3(90, 90, 0), glm::vec3(0.03, 0.03, 0.03)); // move transform3 by -0.5 each loop.
		}

		if (transform2.GetPos()->x > 30)		// If the X position of transform2 is greater than 30.
		{
			r1Direct = -10;						// set r1Direct to -10.
		}
		if (transform2.GetPos()->x < -30)		// If the X position of transform2 is less than -30.
		{
			r1Direct = 10;						// set r1Direct to 10.
		}

		if (transform3.GetPos()->x > 30)		// If the X position of transform3 is greater than 30.
		{
			r2Direct = -10;						// set 21Direct to -10.
		}
		if (transform3.GetPos()->x < -30)		// If the X position of transform3 is less than -30.
		{
			r2Direct = 10;						// set 21Direct to 10.
		}

	}
}

void MainGame::processInput()
{
	SDL_Event evnt;								// Create the event.
	
		while (SDL_PollEvent(&evnt))			// Get and process events.
		{
			switch (evnt.type)					// Switch statement to check Event type.
			{
			case SDL_QUIT:						// Case quit event.
				_gameState = GameState::EXIT;	// Set gamestate to EXIT.
				break;							

			case SDL_KEYDOWN:					// Case keydown event. 
				switch (evnt.key.keysym.sym)	// Switch statement to check keyboard input.
				{
				case SDLK_LEFT:					// Case left arrow.
					transform.transformObj(-0.5, 1);	// Call transform.transformObj with inputPos = -0.5 and direction = 1.
					break;						

				case SDLK_RIGHT:				// Case right arrow.
					transform.transformObj(0.5, 3);		// Call transform.transformObj with inputPos = 0.5 and direction = 3.
					break;						
				}
				break;							

			case SDL_KEYUP:						// Case key up event.

				switch (evnt.key.keysym.sym)	// Switch statement to check keyboard input.
				{ 			
				case SDLK_LEFT:					// Case left arrow.
					transform.resetObjRot(0.5);	// Call transform.resetObjRot with inputPos = 0.5.
					break;
				case SDLK_RIGHT:				// Case right arrow.
					transform.resetObjRot(-0.5);	// Call transform.resetObjRot with inputPos = -0.5.
					break;
				}
				break;

			}
		}
}


void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);	// Clear the display.

	shader.Bind();								// Bind the shader.
	
	shader.Update(transform2, myCamera);		// Update the sader useing transform2.
	texture2.Bind(0);							// Bind the shader of texture2.
	meshRing.draw();							// Draw meshRing.

	meshRing.UpdateSphere(*transform2.GetPos() , 4.0f );	// Update the spere of meshRing using the position of transform2 and a radius of 4.

	shader.Update(transform3, myCamera);		// Update the sader useing transform3.
	texture3.Bind(0);							// Bind the shader of texture3.
	meshRing2.draw();							// Draw meshRing2.

	meshRing2.UpdateSphere(*transform3.GetPos(), 5.0f);		// Update the spere of meshRing2 using the position of transform3 and a radius of 5.

	shader.Update(transform, myCamera);			// Update the sader useing transform.
	texture.Bind(0);							// Bind the shader of texture.
	meshShip.draw();							// Draw meshShip.

	meshShip.UpdateSphere(*transform.GetPos(), 4.0f);	// Update the spere of meshShip using the position of transform and a radius of 4.
	
	glEnableClientState(GL_COLOR_ARRAY);		// Call glEnableClientState using GL_COLOUR_ARRAY.
	glEnd();									// Call glEND.

	_gameDisplay.swapBuffer();					// Swap the buffer.
}

