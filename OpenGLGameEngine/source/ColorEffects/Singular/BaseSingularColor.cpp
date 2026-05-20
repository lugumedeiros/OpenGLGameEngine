#include "BaseSingularColor.h"

std::vector<float*> colorEffects::BaseSingularColor::getColorPtr()
{
	return std::vector<float*>{&red, &green, &blue};
}

void colorEffects::BaseSingularColor::setColor(float r, float g, float b) {
	setRed(r);
	setGreen(g);
	setBlue(b);
}

void colorEffects::BaseSingularColor::incrementColor(float r, float g, float b){
	setRed(red + r);
	setGreen(green + g);
	setBlue(blue + b);
}

void colorEffects::BaseSingularColor::setRed(float r){
	if (r < 0.0f) {
		red = 0.0f;
	}
	else if (r > 1.0f) {
		red = 1.0f;
	}
	else {
		red = r;
	}
}

void colorEffects::BaseSingularColor::setGreen(float g){
	if (g < 0.0f) {
		green = 0.0f;
	}
	else if (g > 1.0f) {
		green = 1.0f;
	}
	else {
		green = g;
	}
}

void colorEffects::BaseSingularColor::setBlue(float b){
	if (b < 0.0f) {
		blue = 0.0f;
	}
	else if (b > 1.0f) {
		blue = 1.0f;
	}
	else {
		blue = b;
	}
}

void colorEffects::BaseSingularColor::incrementPtrColor(float* color, float increment){
	*color += increment;
	if (*color < 0.0f) {
		*color = 0.0f;
	}
	else if (*color > 1.0f) {
		*color = 1.0f;
	}
	else {
		*color = *color;
	}
}
