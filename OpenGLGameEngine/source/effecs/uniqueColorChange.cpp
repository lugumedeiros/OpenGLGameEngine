#include "../../include/effecs/uniqueColorChange.h"

UniqueColorChange::UniqueColorChange(float r, float g, float b, float a): r(r), g(g), b(b), a(a){
}

void UniqueColorChange::advance() {
	if (isIncreasing) {
		if (*selected >= 1.0f) {
			isIncreasing = false;
			*selected = 1.0f;
		}
		else {
			*selected += increment;
		}
		return;
	}
	else {
		if (*selected <= 0.0f) {
			isIncreasing = true;
			*selected = 0.0f;
			next();
		}
		else {
			*selected -= increment;
		}
	}
}

void UniqueColorChange::next() {
	if (selected == &r) {
		selected = &g;
	}
	else if (selected == &g) {
		selected = &b;
	}
	else if (selected == &b) {
		selected = &r;
	}
}
