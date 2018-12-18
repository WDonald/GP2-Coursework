#include "transform.h"
#include <SDL\SDL.h>
#include <GL/glew.h>

using namespace std;

Transform transform;

void Transform::transformObj(float inputPos, int direction)
{
	if (direction != currentDirection)			// If direction is not equal to currentDirection.
	{
		decreaseCounter = counter;				// Set decreaseCounter to the vslue of counter.
		currentDirection = direction;			// Set currenDirection to the vslue of direction.
		counter = 0;							// Set counter to 0.
		canGoBack = true;						// Set canGoBack to true.
	}
	else
	{
		canGoBack = false;						// Set canGoBack to false.
	}

	if (transform.pos.x > -25 && transform.pos.x < 25)		// If the X position of transform is within the boundary of -25 and 25.
	{
		if (counter > 0)						// If counter is greater than 0.
		{
			transform.SetPos(glm::vec3(inputPos * 25 * decreaseCounter, -15.0, 32.5));		// Set the position of transform in X-axis to inputPos * 25 * decreaseCounter.
			decreaseCounter -= 0.1;				// Subtract 0.1 from decreaseCounter. 
		}
	}
	else if(canGoBack)							// If canGoBack is true.
	{
		transform.SetPos(glm::vec3(transform.pos.x - inputPos, -15.0, 32.5));	// Move the transform by negitive inputpos. 
	}
	
	if (transform.rot.z >-0.5 && transform.rot.z < 0.5)		// If the Z rotation of transform is within the boundary of -0.5 and 0.5.
	{
		transform.SetRot(glm::vec3(0.0, 0.0, inputPos*counter));	// Rotate transform in the Z-axis by inputPos multiplied by counter.
		counter += 0.1;							// Increase counter by 0.1.
	}
	transform.SetScale(glm::vec3(sinf(0.5), sinf(0.5), sinf(0.5)));	// Set the scale of transform.
}

void Transform::resetObjRot(float inputPos)		
{
	if (transform.rot.z != 0)					// If the Z rotation of transform is not zero.
 	{
		transform.SetRot(glm::vec3(0.0, 0.0, 0.0));		// Reset the rotation of transform.
	}
}

void Transform::setTransform()
{
	transform.SetPos(glm::vec3(0.0, -15.0, 32.5));		// Set the positon of transform to (0.0, -15.0, 32.5).
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));			// Set the rotation of transform to (0, 0, 0).
	transform.SetScale(glm::vec3(sinf(0.5), sinf(0.5), sinf(0.5)));		// Set the scale of transfor to (sinf(0.5), sinf(0.5), sinf(0.5)).
}


