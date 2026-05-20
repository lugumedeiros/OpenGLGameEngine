#pragma once
#include "../../BaseSingularColor.h"
#include <random>

class RandomTransition : public colorEffects::BaseSingularColor {
public:
	RandomTransition(float r, float g, float b) : BaseSingularColor(r, g, b) {}
	~RandomTransition() = default;
	void advanceEffect() override;
	void setIntensity(float i);
private:
	float intensity = 0.01f;
};