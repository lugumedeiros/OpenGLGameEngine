#pragma once
#include "../../BaseSingularColor.h"
#include <vector>

class PrimitiveTransition : public colorEffects::BaseSingularColor {
public:
	PrimitiveTransition(float r, float g, float b) : BaseSingularColor(r, g, b) {}
	~PrimitiveTransition() = default;
	void advanceEffect() override;

private:
	float* currentColorPtr = &red;
	size_t currentColorIndex = 0;
	std::vector<float*> order = { &red, &green, &blue };
	void advanceToNextColor();
	float intensity = 0.01f;
	bool increasing = true;
};