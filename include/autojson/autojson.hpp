#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <string.h>

namespace autojson
{
	class json_writer;

    template<typename T>
    inline void jsonify(const T& rhs, json_writer& ____auto_jsonify)
    {
#if defined(__FUNCSIG__)
        static_assert(sizeof(T) == -1, "(" __FUNCSIG__ ") Attempted to jsonify typee with no jsonify implementation; make sure you have #included all necessary headers");
#elif defined(__PRETTY_FUNCTION__)
		static_assert(sizeof(T) == -1, "(" __PRETTY_FUNCTION__") Attempted to jsonify typee with no jsonify implementation; make sure you have #included all necessary headers");
#else
		static_assert(sizeof(T) == -1, "Attempted to jsonify typee with no jsonify implementation; make sure you have #included all necessary headers");
#endif
    }

    class json_writer
    {
    public:
		inline void begin_object()
		{
			m_Buffer += "{";
		}

		inline void end_object()
		{
			if (m_Buffer[m_Buffer.size() - 1] == ',')
			{
				m_Buffer[m_Buffer.size() - 1] = '}';
			}
			else
			{
				m_Buffer += "}";
			}
		}

        template <typename T>
        inline void write_variable(const char* name, size_t nameLen, const T& value)
        {
			m_Buffer.reserve(m_Buffer.size() + nameLen + 5);
			m_Buffer += '"';
			m_Buffer.append(name);
			m_Buffer.append("\":");
			jsonify(value, *this);
			m_Buffer.append(",");
        }

		void append(const std::string& rhs)
		{
			m_Buffer.reserve(m_Buffer.size() + rhs.size() + 1);
			m_Buffer.append(rhs);
		}

        inline std::string get_json()
        {
            return m_Buffer;
        }

    private:
        std::string m_Buffer;
    };

	namespace JSON
	{
		template <typename T>
		std::string stringify(const T& rhs)
		{
			json_writer writer;
			jsonify(rhs, writer);
			return writer.get_json();
		}

		// lifted from https://stackoverflow.com/questions/7724448/simple-json-string-escape-for-c/33799784#33799784
		std::string escape(const std::string &s) {
			std::ostringstream o;
			for (auto c = s.cbegin(); c != s.cend(); c++) {
				if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
					o << "\\u"
						<< std::hex << std::setw(4) << std::setfill('0') << (int)*c;
				}
				else {
					o << *c;
				}
			}
			return o.str();
		}
	}
}

#define JSONIFY_METHOD(T) template <> inline void autojson::jsonify<T>(const T& rhs, autojson::json_writer& ____auto_jsonify)
#define BEGIN_JSON_OBJ()				____auto_jsonify.begin_object()
#define WRITE_VARIABLE(variable)		____auto_jsonify.write_variable(#variable, strlen(#variable), rhs.variable)
#define WRITE_VALUE(value)				____auto_jsonify.append(value)
#define END_JSON_OBJ()					____auto_jsonify.end_object()