#pragma once
#include <string>


class KeyObj {
public:
    KeyObj(std::string_view key, int glfwCode);
    KeyObj(std::string_view key, int glfwCode, bool shouldRepeat, int firstRepeatDelay, int repeatDelay);

    void setRepeat(bool shouldRepeat, int firstRepeatDelay, int repeatDelay);
    bool press();
    bool release();
    const std::string& getKey() const { return key; };

private:
    // Basic config
    std::string key{""};
    int glfwCode{0};
    bool isPressed{false};

    // RepeatConfig
    bool shouldRepeat{false};
    bool hasStartedRepeat{false};
    int firstRepeatDelay{1};
    int repeatDelay{1};
    int currentRepeatPos{0};
    void resetRepeatStatus();

};