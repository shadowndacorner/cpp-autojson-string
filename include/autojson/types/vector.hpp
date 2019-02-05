/*
MIT License

Copyright (c) 2019 Ian Diaz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include "../autojson.hpp"
#include <vector>

namespace autojson
{
	// Not using macro due to template
	template<typename T>
	inline void jsonify(const std::vector<T>& rhs, autojson::json_writer& ____auto_jsonify)
	{
		WRITE_VALUE("[");
		for (size_t i = 0; i < rhs.size(); ++i)
		{
			jsonify(rhs[i], ____auto_jsonify);
			if (i < rhs.size() - 1)
			{
				WRITE_VALUE(",");
			}
		}
		WRITE_VALUE("]");
	}
}