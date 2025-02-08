#pragma once
#include "iGraphics.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")  // Link Windows multimedia library

class Animation {
private:
	std::vector<int> frames;  // Stores image IDs
	int frameIndex;           // Current animation frame
	int totalFrames;          // Total number of frames
	bool repeatable;          // Should the animation repeat?
	int intervalMS;           // Frame change interval (in milliseconds)
	bool isFinished;          // Flag to check if animation ended
	std::string soundPath;    // Path to the sound file
	bool soundPlaying;        // Is sound currently playing?

public:
	// Constructor: Load images automatically
	Animation(const std::string& folder, const std::string& filePrefix, int totalFrames, bool isRepeatable, int intervalMS, const std::string& soundFile = "")
		: frameIndex(0), totalFrames(totalFrames), repeatable(isRepeatable), intervalMS(intervalMS), isFinished(false), soundPath(soundFile), soundPlaying(false) {
		loadImages(folder, filePrefix);
	}

	// Load images from folder
	void loadImages(const std::string& folder, const std::string& filePrefix) {
		std::string framePath;
		for (int i = 0; i < totalFrames; i++) {
			framePath = folder + "/" + filePrefix + " (" + std::to_string(i + 1) + ").png";
			int imageID = iLoadImage(const_cast<char*>(framePath.c_str()));

			if (imageID == -1) {
				std::cerr << "Failed to load image: " << framePath << std::endl;
			}
			frames.push_back(imageID);
		}
	}

	// Play sound if available
	void playSound() {
		if (!soundPath.empty() && !soundPlaying) {
			PlaySound(soundPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
			soundPlaying = true;
		}
	}

	// Stop sound
	void stopSound() {
		PlaySound(NULL, NULL, 0);  // Stop currently playing sound
		soundPlaying = false;
	}

	// Update animation frame
	void updateFrame() {
		if (isFinished) return;  // Stop updating if animation is finished

		if (frameIndex == 0) {
			playSound();  // Start sound when animation starts
		}

		frameIndex++;
		if (frameIndex >= totalFrames) {
			if (repeatable) {
				frameIndex = 0;  // Loop animation
			}
			else {
				frameIndex = totalFrames - 1;  // Stop at last frame
				isFinished = true;
				stopSound();  // Stop sound when animation finishes
			}
		}
	}

	// Render the animation
	void render(int x, int y, int width, int height) const {
		if (!frames.empty()) {
			iShowImage(x, y, width, height, frames[frameIndex]);
		}
	}

	// Start the animation from the beginning
	void reset() {
		frameIndex = 0;
		isFinished = false;
		playSound();  // Restart sound if applicable
	}

	// Check if the animation has finished (for non-repeatable animations)
	bool hasFinished() const {
		return isFinished;
	}

	// Get the interval time for the iGraphics timer
	int getInterval() const {
		return intervalMS;
	}
};
