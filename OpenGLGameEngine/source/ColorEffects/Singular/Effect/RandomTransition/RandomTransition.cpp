#include "RandomTransition.h"
#include <vector>
#include <random>

void RandomTransition::advanceEffect(){
	float changeRed = (rand() % 2) == 0? intensity : -intensity;
	float changeGreen = (rand() % 2) == 0? intensity : -intensity;
	float changeBlue = (rand() % 2) == 0 ? intensity : -intensity;
	incrementColor(changeRed, changeGreen, changeBlue);
}

void RandomTransition::setIntensity(float i){
	if (i > 1.0f) {
		intensity = 1.0f;
	}
	else if (i < 0.0f) {
		intensity = 0.0f;
	}
	else {
		intensity = i;
	}
}
