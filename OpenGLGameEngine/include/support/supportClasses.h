#pragma once

template<typename T>
class ConfigValue {
public:
	ConfigValue(T val) :val(val), defVal(val) {}

	void set(T newVal) { val = newVal; }
	void setRestore(T val) { defVal = val; }
	void setInc(T increment) { incVal = increment; }
	void restore() { val = defVal; }
	void inc(T val) { this->val += val; }
	void inc() { val += incVal; }
	void dec(T val) { this->val -= val; }
	void dec() { val -= incVal; }
	operator T() const { return val; }

private:
	T val;
	T defVal;
	T incVal;
};