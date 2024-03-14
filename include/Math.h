#include <cmath>
#include <raymath.h>
#include <stdio.h>
#include <ostream>
#include <format>

typedef Vector3 Vec3;
typedef Vector2 Vec2;

constexpr float deg2Radians(float f) { return (f * M_PI) / 180.0f; };

inline std::ostream& operator << (std::ostream& o, const Vector3& v){
    char buf[512];
    snprintf(buf, 512, "(%.2f, %.2f, %.2f)", v.x, v.y, v.z);
    o << buf;
    return o;
};

inline std::ostream& operator << (std::ostream& o, const Matrix& M){
    char r0[512], r1[512], r2[512], r3[512];

    snprintf(r0, 512, "%f %f %f %f\n", M.m0, M.m4, M.m8, M.m12);
    snprintf(r1, 512, "%f %f %f %f\n", M.m1, M.m5, M.m9, M.m13);
    snprintf(r2, 512, "%f %f %f %f\n", M.m2, M.m6, M.m10, M.m14);
    snprintf(r3, 512, "%f %f %f %f", M.m3, M.m7, M.m11, M.m15);

    o << r0 << r1 << r2 << r3;
    return o;
}

inline bool operator==(const Vec3& a, const Vec3& b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(const Vec3& a, const Vec3& b){ return !(a==b); }
inline Vec3 operator+(const Vec3&a, const Vec3& b){ return Vector3Add(a, b); }
inline Vec3 operator-(const Vec3&a, const Vec3& b){ return Vector3Subtract(a, b); }
inline Vec3 operator*(const Vec3&a, float f){ return Vector3Scale(a, f); }
inline Vec3 operator*(float f, const Vec3&a){ return Vector3Scale(a, f); }

//Element wise division for vec3
inline Vec3 operator/(const Vec3& v, const Vec3& w){
    Vec3 ans;
    ans.x = v.x / w.x;
    ans.y = v.y / w.y;
    ans.z = v.z / w.z;
    return ans;
}
