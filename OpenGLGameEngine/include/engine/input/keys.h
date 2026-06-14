#pragma once
#include <string>

// TODO: DELAY IS LINKED TO FRAMERATE
class KeyObj {
public:
    KeyObj(std::string_view key, int glfwCode);
    KeyObj(std::string_view key, int glfwCode, bool shouldRepeat, double firstRepeatDelay, double repeatDelay);

    void setRepeat(bool shouldRepeat, double firstRepeatDelay, double repeatDelay);
    bool press(double newEventTime);
    bool release();
    const std::string& getKey() const { return key; };

private:
    // Basic config
    std::string key{""};
    int glfwCode{0};
    bool isPressed{false};
    double lastEventTime{ 0.0 };

    // RepeatConfig
    bool shouldRepeat{false};
    bool hasStartedRepeat{false};
    double firstRepeatDelay{1.0};
    double repeatDelay{1.0};
    double currentRepeatPos{0.0};
    void resetRepeatStatus();
};