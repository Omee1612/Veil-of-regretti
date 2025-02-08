#include "Animation.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

int frame = 0;
bool onFirstWinLastFrame = false;
bool continueToMenu = false;

std::vector<std::unique_ptr<Animation>> animations;  // Animation vector
size_t currentAnimationIndex = 0;  // Track the current animation index
int animationTimerID = -1;  // Global variable to store timer ID
void startAnimationTimer();

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void iDraw()
{
	iClear();

	if (!animations.empty()) {
		animations[currentAnimationIndex]->render(0, 0, 800, 600);

		if (animations[currentAnimationIndex]->hasFinished()) {
			if (currentAnimationIndex + 1 < animations.size()) {
				currentAnimationIndex++;  // Move to the next animation
				animations[currentAnimationIndex]->reset();
				startAnimationTimer();
			}
			else {
				onFirstWinLastFrame = true;
			}
		}
	}

	if (onFirstWinLastFrame && continueToMenu) {
		iText(400, 300, "edik menu thakbe", GLUT_BITMAP_HELVETICA_10);
	}
}

void updateFrame() {
	if (!animations.empty()) {
		animations[currentAnimationIndex]->updateFrame();
	}
}

/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my) {}

//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my) {}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == '\r') {}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc.
*/
void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_HOME)
	{
		if (onFirstWinLastFrame)
		{
			continueToMenu = true;
		}
	}
}

void startAnimationTimer() {
	if (animationTimerID != -1) {
		iPauseTimer(animationTimerID);  // Stop the previous timer
	}
	animationTimerID = iSetTimer(animations[currentAnimationIndex]->getInterval(), updateFrame);
}
int main() {
	iInitialize(800, 600, "Veil of Regret");  // Initialize first!

	animations.emplace_back(std::make_unique<Animation>("Images/clockTicking", "clock", 165, false, 44, "Audio/introSound.wav"));
	animations.emplace_back(std::make_unique<Animation>("Images/firstWindow", "window", 25, false, 500, "Audio/firstWindowMusic.wav", true));

	if (animations.empty()) {
		std::cerr << "Error: Failed to initialize animations" << std::endl;
		return -1;
	}

	startAnimationTimer();

	iStart();
	return 0;
}
