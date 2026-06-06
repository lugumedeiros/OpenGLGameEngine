#pragma once
#include <algorithm>

struct Vector2 {
public:
    float x{ 1.0f };
    float y{ 1.0f };

    Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {}
};

struct Vector3 {
public:
    float x{ 1.0f };
    float y{ 1.0f };
    float z{ 1.0f };

    Vector3() = default;
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {
    }

    explicit Vector3(const Vector2& v, float z = 1.0f)
        : x(v.x), y(v.y), z(z) {
    }
};

struct Vector4 {
public:
    float x{ 1.0f };
    float y{ 1.0f };
    float z{ 1.0f };
    float w{ 1.0f };

    Vector4() = default;
    Vector4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {
    }

    explicit Vector4(const Vector3& v, float w = 1.0f)
        : x(v.x), y(v.y), z(v.z), w(w) {
    }

    void normalizeScale() {
        float greater = std::max(std::abs(x), std::abs(y));
        greater = std::max(greater, std::abs(z));
        greater = std::max(greater, std::abs(w));
        if (greater > 1.0f) {
            x /= greater;
            y /= greater;
            z /= greater;
            w /= greater;
        }
    }
};