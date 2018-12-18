#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();						// Constructor.
	~MainGame();					// Destructor.

	void run();						// Run the game when called.
	bool checkCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad, int ringNo);	// Check for collisions when called.


private:

	void initSystems();				// Initilisatins.
	void processInput();			// Process keybord input.
	void gameLoop();				// Loop code that requiers to be constanty updated.
	void drawGame();				// Draw to screen.

	Display _gameDisplay;			// The display.
	GameState _gameState;			// The state the game is in.
	
	Mesh meshShip;					// Mesh for the ship.
	Mesh meshRing;					// Mesh for the first ring.
	Mesh meshRing2;					// Mesh for the second ring.
	
	GameCamera myCamera;			// The Game camera.
	
	//Textures//
	Texture texture;				// Texture for the sip.
	Texture texture2;				// Texture for the first ring.
	Texture texture3;				// Texture for the second Ring.

	Shader shader;					// Shader creation.

	int score;						// Keeps track of the score.
	int r1Direct;					// Used to move ring 1 in the X-axis.
	int r2Direct;					// Used to move ring 2 in the X-axis.

	Transform transform2 = Transform(glm::vec3(-30, -10, 90), glm::vec3(90, 180, 0), glm::vec3(0.2, 0.2, 0.2));			// Transform used to move the first ring.
	Transform transform3 = Transform(glm::vec3(30, -10, 90), glm::vec3(90, 270, 0), glm::vec3(0.03, 0.03, 0.03));		// Transform used to move the second ring.

};

