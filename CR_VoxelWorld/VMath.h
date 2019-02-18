#pragma once
struct Vec3c {
	union {
		struct {
			unsigned char x, y, z;
		};
		unsigned char data[3];
	};
public:
	Vec3c() : x(0), y(0), z(0) {}
	Vec3c(char x, char y, char z) : x(x), y(y), z(z) {}

	inline Vec3c operator+(const Vec3c& o) const {
		return {x + o.x, y + o.y, z + o.z};
	}
	inline Vec3c operator-(const Vec3c& o) const {
		return {x - o.x, y - o.y, z - o.z};
	}
	inline void operator+=(const Vec3c& o) {
		x += o.x;
		y += o.y;
		z += o.z;
	}
	inline void operator-=(const Vec3c& o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
	}

	inline friend Vec3c operator*(const Vec3c& v, char c) {
		return {v.x * c, v.y * c, v.z * c};
	}
	inline friend Vec3c operator*(char c, const Vec3c& v) {
		return {v.x * c, v.y * c, v.z * c};
	}

	inline friend Vec3c operator/(const Vec3c& v, char c) {
		return {v.x / c, v.y / c, v.z / c};
	}
	inline friend Vec3c operator/(char c, const Vec3c& v) {
		return {c / v.x, c / v.y, c / v.z};
	}

	inline friend Vec3c operator*(const Vec3c& a, const Vec3c& b) {
		return {a.x * b.x, a.y * b.y, a.z * b.z};
	}
	inline friend Vec3c operator/(const Vec3c& a, const Vec3c& b) {
		return {a.x / b.x, a.y / b.y, a.z / b.z};
	}

	inline bool operator==(const Vec3c& o) const {
		return x == o.x && y == o.y && z == o.z;
	}
	inline bool operator!=(const Vec3c& o) const {
		return x != o.x || y != o.y || z != o.z;
	}

	inline const unsigned char& operator[](int index) const {
		return data[index];
	}
	inline unsigned char& operator[](int index) {
		return data[index];
	}
};