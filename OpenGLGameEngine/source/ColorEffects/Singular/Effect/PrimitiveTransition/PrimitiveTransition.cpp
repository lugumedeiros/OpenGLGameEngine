#include "PrimitiveTransition.h"

void PrimitiveTransition::advanceEffect(){
	if (increasing){
		if (*currentColorPtr >= 1.0f) {
			increasing = false;
			return;
		}
		incrementPtrColor(currentColorPtr, intensity);
	}
	else {
		if (*currentColorPtr <= 0.0f) {
			increasing = true;
			advanceToNextColor();
			return;
		}
		incrementPtrColor(currentColorPtr, -intensity);
	}
}

void PrimitiveTransition::advanceToNextColor(){
	currentColorIndex = (currentColorIndex + 1) % order.size();
	currentColorPtr = order[currentColorIndex];
}
