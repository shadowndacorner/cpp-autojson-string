#pragma once
#include "../autojson.hpp"

JSONIFY_METHOD(std::string)
{
    WRITE_VALUE('"' + JSON::escape(rhs) + '"');
}