#pragma once

class KeyObj {
public:
    KeyObj(char key, int glfwCode);
    KeyObj(char key, int glfwCode, bool shouldRepeat, int firstRepeatDelay, int repeatDelay);
    //~KeyObj();
    void setRepeat(bool shouldRepeat, int firstRepeatDelay, int repeatDelay);
    bool press();
    bool release();    

private:
    // Basic config
    int glfwCode{0};
    char key{0};
    bool isPressed{false};

    // RepeatConfig
    bool shouldRepeat{false};
    bool hasStartedRepeat{false};
    int firstRepeatDelay{1};
    int repeatDelay{1};
    int currentRepeatPos{0};
    void resetRepeatStatus();

};