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