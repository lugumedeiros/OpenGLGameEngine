#include "../../include/input/keys.h"

KeyObj::KeyObj(char key, int glfwCode) :key(key), glfwCode(glfwCode) {
}

KeyObj::KeyObj(char key, int glfwCode, bool shouldRepeat, int firstRepeatDelay, int repeatDelay) 
	:key(key), glfwCode(glfwCode), shouldRepeat(shouldRepeat), firstRepeatDelay(firstRepeatDelay), repeatDelay(repeatDelay) {
}

void KeyObj::setRepeat(bool shouldRepeat, int firstRepeatDelay, int repeatDelay) {
	this->shouldRepeat = shouldRepeat;
	this->firstRepeatDelay = firstRepeatDelay;
	this->repeatDelay = repeatDelay;
	currentRepeatPos = 0;
}

// Returns true when the key action should be triggered:
// - On the initial press.
// - On auto-repeat events if repeat is enabled.
//
// Returns false when:
// - The key is already pressed and repeat is disabled.
// - The repeat delay has not yet elapsed.
bool KeyObj::press(){
	// First Press
	if (!isPressed) {
		isPressed = true;
		return true;
	}
	// Pressing but repeat is disabled
	if (!shouldRepeat) {
		return false;
	}
	
	// First repeat logic
	if (!hasStartedRepeat) {
		if (currentRepeatPos >= firstRepeatDelay) {
			currentRepeatPos = 0;
			hasStartedRepeat = true;
			return true;
		} else {
			currentRepeatPos++;
			return false;
		}
	}

	// Onward Repeat logic
	if (currentRepeatPos >= repeatDelay) {
		currentRepeatPos = 0;
		return true;
	}
	else {
		currentRepeatPos++;
		return false;
	}
}

// Releases the key and clears all repeat-related state.
//
// Returns true if the key was previously pressed.
// Returns false if the key was already released.
bool KeyObj::release(){
	if (isPressed == false) {
		return false;
	}
	isPressed = false;
	resetRepeatStatus();
	return true;
}

void KeyObj::resetRepeatStatus() {
	hasStartedRepeat = false;
	currentRepeatPos = 0;
}
