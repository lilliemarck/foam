#pragma once

#include <cmath>
#include <limits>
#include <ostream>

namespace foam {

template <typename T>
class vector2 {
public:
	vector2() {
	}

	vector2(T const& x, T const& y) : elements_{x, y} {
	}

	T& x() {
		return elements_[0];
	}

	T const& x() const {
		return elements_[0];
	}

	T& y() {
		return elements_[1];
	}

	T const& y() const {
		return elements_[1];
	}

private:
	T elements_[2];
};

using vector2i = vector2<int>;

template <typename T>
vector2<T> operator*(vector2<T> const& lhs, T const& rhs) {
	return {lhs.x() * rhs, lhs.y() * rhs};
}

template <typename T>
vector2<T> operator*(T const& lhs, vector2<T> const& rhs) {
	return {lhs * rhs.x(), lhs * rhs.y()};
}

template <typename T>
vector2<T> operator/(vector2<T> const& lhs, T const& rhs) {
	return {lhs.x() / rhs, lhs.y() / rhs};
}

template <typename T>
vector2<T> operator+(vector2<T> const& lhs, vector2<T> const& rhs) {
	return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

template <typename T>
vector2<T> operator-(vector2<T> const& lhs, vector2<T> const& rhs) {
	return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

template <typename T>
vector2<T>& operator+=(vector2<T>& lhs, vector2<T> const& rhs) {
	lhs.x() += rhs.x();
	lhs.y() += rhs.y();
	return lhs;
}

template <typename T>
vector2<T>& operator-=(vector2<T>& lhs, vector2<T> const& rhs) {
	lhs.x() -= rhs.x();
	lhs.y() -= rhs.y();
	return lhs;
}

template <typename T>
T dot(vector2<T> const& lhs, vector2<T> const& rhs) {
	return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

template <typename T>
T distance(vector2<T> const& lhs, vector2<T> const& rhs) {
	return length(rhs - lhs);
}

template <typename T>
T length(vector2<T> const& vec) {
	return std::sqrt(vec.x() * vec.x() + vec.y() * vec.y());
}

template <typename T>
vector2<T> norm(vector2<T> const& vec) {
	float length = foam::length(vec);
	if (length > std::numeric_limits<float>::epsilon()) {
		return vec / length;
	}
	else {
		return vec;
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, vector2<T> const& v) {
	os << '[' << v.x() << ", " << v.y() << ']';
	return os;
}

} // namespace foam
