#pragma once
#include  <iostream>

/**
 * Example:
 * @code
 * ConfigValue<float> speed(5.0f, 0.5f, 1.0f, 20.0f);
 *
 * speed.inc();      // 5.5
 * speed.inc(2.0f);  // 7.5
 * speed.dec();      // 7.0
 *
 * speed.set(100.0f); // Clamped to 20.0
 * speed.restore();   // Back to 5.0
 * @endcode
 */

template<typename T>
class ConfigValue {
public:
	ConfigValue(T val) :val(val), defVal(val), incVal(val) {}
	ConfigValue(T val, T increment) :val(val), defVal(val), incVal(increment) {}
	ConfigValue(T val, T increment, T min, T max) :val(val), defVal(val), incVal(increment), min(min), max(max) {
		hasMinMax = true;
	}

	void set(T newVal) {
		if (hasMinMax) {
			newVal = clamp(newVal);
		}
		val = newVal;
	}

	void setRestore(T val) {
		if (hasMinMax) {
			val = clamp(val);
		}
		defVal = val;
	}

	void setInc(T increment) { incVal = increment; }
	void restore() { set(defVal); }
	
	void inc() { inc(incVal); }
	void dec() { dec(incVal); }
	void dec(T val) { inc(-val); }

	void inc(T val) {
		if (hasMinMax) {
			this->val = clamp(this->val + val);
		} else {
			this->val += val;
		}
	}

	void setMinMax(T min, T max) {
		this->min = min;
		this->max = max;
		hasMinMax = true;
	}
	void removeMinMax() { hasMinMax = false; }
	T get() { return val; }
	T getRestore() { return defVal; }
	T getInc() { return incVal; }

	operator T() const { return val; }

private:
	T val;
	T defVal;
	T incVal;
	T min{};
	T max{};
	bool hasMinMax{ false };

	T clamp(T val) const {
		if (val > max) {
			return max;
		}
		if (val < min) {
			return min;
		}
		return val;
	}
};