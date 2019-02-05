#pragma once
#include "../autojson.hpp"

JSONIFY_METHOD(int)
{
	WRITE_VALUE(std::to_string(rhs));
}

JSONIFY_METHOD(unsigned int)
{
	WRITE_VALUE(std::to_string(rhs));
}

JSONIFY_METHOD(long long)
{
	WRITE_VALUE(std::to_string(rhs));
}

JSONIFY_METHOD(unsigned long long)
{
	WRITE_VALUE(std::to_string(rhs));
}

JSONIFY_METHOD(float)
{
	WRITE_VALUE(std::to_string(rhs));
}

JSONIFY_METHOD(double)
{
	WRITE_VALUE(std::to_string(rhs));
}