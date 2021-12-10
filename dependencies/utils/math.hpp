#pragma once

#define M_PI 3.14159265358979323846f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))

class Vector2
{
public:
	float x, y;

	Vector2() { };

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	};

	bool is_valid()
	{
		return (x != 0 && y != 0);
	}

	float length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	float distance(Vector2 b)
	{
		return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
	}

	void normalize()
	{

		if (x < -89)
			x = -89;


		else if (x > 89)
			x = 89;


		if (y < -360)
			y += 360;


		else if (y > 360)
			y -= 360;
	}

	Vector2& operator*=(float input)
	{
		x *= input;
		y *= input;
		return *this;
	}
};

class Vector3
{
public:
	Vector3()
	{
		x = y = z = 0.f;
	}

	Vector3(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	float x, y, z;

	Vector3 operator+(const Vector3& input) const
	{
		return Vector3{ x + input.x, y + input.y, z + input.z };
	}

	Vector3 operator-(const Vector3& input) const
	{
		return Vector3{ x - input.x, y - input.y, z - input.z };
	}

	Vector3 operator/(float input) const
	{
		return Vector3{ x / input, y / input, z / input };
	}

	Vector3 operator*(float input) const
	{
		return Vector3{ x * input, y * input, z * input };
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		return *this;
	}

	Vector3& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		return *this;
	}

	bool operator==(const Vector3& input) const
	{
		return x == input.x && y == input.y && z == input.z;
	}

	void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	float clamp0to1(float value)
	{
		float result;
		if (value < 0)
		{
			result = 0;
		}
		else if (value > 1.f)
		{
			result = 1.f;
		}
		else
		{
			result = value;
		}
		return result;
	}

	float Lerp()
	{
		return x + (y - x) * clamp0to1(z);
	}

	float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	float length() const
	{
		return (float)sqrt(length_sqr());
	}

	float length_2d() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	Vector3 normalize()
	{
		Vector3 out = *this;
		auto len = length();
		if (!len)
			return *this;

		out.x /= len;
		out.y /= len;
		out.z /= len;
		return out;
	}

	Vector3 cross(Vector3 rhs)
	{
		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	float unity_magnitude()
	{
		return (float)sqrt((double)(x * x + y * y + z * z));
	}

	Vector3 unity_normalize()
	{
		float num = unity_magnitude();
		if (num > 1E-05f)
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}

		return { x,y,z };
	}

	Vector3 normalized() const
	{
		return { x == 0 ? 0 : x / length(), y == 0 ? 0 : y / length(), z == 0 ? 0 : z / length() };
	}

	float dot(Vector3 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	float distance(Vector3 input) const
	{
		return (*this - input).length();
	}

	float distancesqr(Vector3 input) const
	{
		Vector3 dif = { x - input.x, y - input.y, z - input.z };
		return dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;
	}

	float distance_2d(Vector3 input) const
	{
		return (*this - input).length_2d();
	}

	void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));
		z = 0.f;
		return;
	}

	bool is_valid() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}
};

class Vector4
{
public:
	Vector4()
	{
		x = y = z = w = 0.f;
	}

	Vector4(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	float x, y, z, w;

	Vector4 operator+(const Vector4& input) const
	{
		return Vector4{ x + input.x, y + input.y, z + input.z, w + input.w };
	}

	Vector4 operator-(const Vector4& input) const
	{
		return Vector4{ x - input.x, y - input.y, z - input.z, w - input.w };
	}

	Vector4 operator/(float input) const
	{
		return Vector4{ x / input, y / input, z / input, w / input };
	}

	Vector4 operator*(float input) const
	{
		return Vector4{ x * input, y * input, z * input, w * input };
	}

	Vector4& operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	Vector4& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		w /= input;
		return *this;
	}

	Vector4& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		w *= input;
		return *this;
	}

	bool operator==(const Vector4& input) const
	{
		return x == input.x && y == input.y && z == input.z && w == input.w;
	}

	void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
		w = std::abs(w);
	}

	float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	float length() const
	{
		return (float)sqrt(length_sqr());
	}

	float length_2d() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	Vector4 normalized() const
	{
		return { x / length(), y / length(), z / length(), w / length() };
	}

	float dot(Vector4 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z) + (w * input.w);
	}

	float distance(Vector4 input) const
	{
		return (*this - input).length();
	}

	float distance_2d(Vector4 input) const
	{
		return (*this - input).length_2d();
	}
	void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));

		z = 0.f;
		w = 0.f;
	}

	static Vector4 QuaternionLookRotation(Vector3 forward, Vector3 up)
	{
		Vector3 vector = forward.unity_normalize();
		Vector3 Vector2 = (up).cross(vector).unity_normalize();
		Vector3 Vector3 = (vector).cross(Vector2);
		auto m00 = Vector2.x;
		auto m01 = Vector2.y;
		auto m02 = Vector2.z;
		auto m10 = Vector3.x;
		auto m11 = Vector3.y;
		auto m12 = Vector3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;


		float num8 = (m00 + m11) + m22;
		auto quaternion = Vector4();
		if (num8 > 0.f)
		{
			auto num = (float)sqrt(num8 + 1.f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = (float)sqrt(((1.f + m00) - m11) - m22);
			auto num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		auto num5 = (float)sqrt(((1.f + m22) - m00) - m11);
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
	}

	bool is_valid() const
	{
		return !((x == 0.f && y == 0.f && z == 0.f && w == 0.f) || (x == -1.f && y == -1.f && z == -1.f && w == -1.f));
	}
};

Vector3 quaternion_mult(const Vector3* point, Vector4* quat)
{
	float num = quat->x * 2.f;
	float num2 = quat->y * 2.f;
	float num3 = quat->z * 2.f;
	float num4 = quat->x * num;
	float num5 = quat->y * num2;
	float num6 = quat->z * num3;
	float num7 = quat->x * num2;
	float num8 = quat->x * num3;
	float num9 = quat->y * num3;
	float num10 = quat->w * num;
	float num11 = quat->w * num2;
	float num12 = quat->w * num3;
	Vector3 result{};
	result.x = (1.f - (num5 + num6)) * point->x + (num7 - num12) * point->y + (num8 + num11) * point->z;
	result.y = (num7 + num12) * point->x + (1.f - (num4 + num6)) * point->y + (num9 - num10) * point->z;
	result.z = (num8 - num11) * point->x + (num9 + num10) * point->y + (1.f - (num4 + num5)) * point->z;
	return result;
}

float normalize_angle(float angle)
{
	while (angle > 360) angle -= 360;
	while (angle < 0) angle += 360;
	return angle;
}

Vector2 rotate_point(Vector2 point_to_rotate, Vector2 center_point, float angle)
{
	float rad = ((normalize_angle(angle)) * static_cast<float>((3.14159 / 180.f)));
	float s = -sin(rad);
	float c = cos(rad);
	float xnew = point_to_rotate.x * c - point_to_rotate.y * s;
	float znew = point_to_rotate.x * s + point_to_rotate.y * c;
	point_to_rotate.x -= center_point.x;
	point_to_rotate.y -= center_point.y;
	point_to_rotate.x = xnew + center_point.x;
	point_to_rotate.y = znew + center_point.y;
	return point_to_rotate;
}

double to_rad(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}

Vector4 to_quat(Vector3 Euler)
{
	double heading = to_rad(Euler.x);
	double attitude = to_rad(Euler.y);
	double bank = to_rad(Euler.z);

	double c1 = cos(heading / 2);
	double s1 = sin(heading / 2);
	double c2 = cos(attitude / 2);
	double s2 = sin(attitude / 2);
	double c3 = cos(bank / 2);
	double s3 = sin(bank / 2);
	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;
	Vector4 quat;
	quat.w = c1c2 * c3 - s1s2 * s3;
	quat.x = c1c2 * s3 + s1s2 * c3;
	quat.y = s1 * c2 * c3 + c1 * s2 * s3;
	quat.z = c1 * s2 * c3 - s1 * c2 * s3;
	return { quat.y, quat.z, (quat.x * -1), quat.w };
}

Vector2 calculate_angle(Vector3 src, Vector3 dst)
{
	Vector3 dir = src - dst;
	return Vector2{ RAD2DEG(asin(dir.y / dir.length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
}

//float calculate_bullet_drop(float distance, float speed, float gravity)
//{
//	if (distance < 0.001f)
//		return -1;
//
//	float bullet_gravity = 9.81f * gravity;
//	float bullet_travel_time = distance / speed;
//
//	return static_cast<float>(0.5f * bullet_gravity * bullet_travel_time * bullet_travel_time);
//}

float calculate_bullet_drop(float height, float distance, float velocity, float gravity)
{
	float pitch = std::atan2(height, distance);
	float bullet_velocity = velocity * std::cos(pitch);
	float time = distance / bullet_velocity;

	return (0.5f * gravity * time * time) * 10;
}