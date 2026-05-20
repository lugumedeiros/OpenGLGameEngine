#pragma once
#include <vector>

namespace colorEffects {
	class BaseSingularColor {
	public:
		BaseSingularColor(float r, float g, float b) : red(r), green(g), blue(b) {}
		virtual ~BaseSingularColor() = default;
		virtual void advanceEffect() = 0;
		std::vector<float*> getColorPtr();
		std::vector<float> getColor() { return std::vector<float>{red, green, blue}; }
		float* getRedPtr() { return &red; }
		float* getGreenPtr() { return &green; }
		float* getBluePtr() { return &blue; }

	protected:
		float red;
		float green;
		float blue;
		void setColor(float r, float g, float b);
		void incrementColor(float r, float g, float b);
		void setRed(float r);
		void setGreen(float g);
		void setBlue(float b);
		bool isRedMax() { return red >= 1.0f; }
		bool isGreenMax() { return green >= 1.0f; }
		bool isBlueMax() { return blue >= 1.0f; }
		bool isRedMin() { return red <= 0.0f; }
		bool isGreenMin() { return green <= 0.0f; }
		bool isBlueMin() { return blue <= 0.0f; }
		void incrementPtrColor(float* color, float increment);
	};
}