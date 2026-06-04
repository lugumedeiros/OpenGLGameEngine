#pragma once


class UniqueColorChange {
public:
	UniqueColorChange(float r, float g, float b, float a);
	void advance();
	float r, g, b, a;
	float increment{ 0.01f };

private:
	void next();
	float* selected{ &r };
	bool isIncreasing{ true };
};
