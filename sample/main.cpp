#include <iostream>
#include <autojson/autojson.hpp>
#include <autojson/types/vector.hpp>
#include <autojson/types/string.hpp>
#include <autojson/types/inttypes.hpp>

struct serializable
{
	int test;
	double anotherTest;
	std::string someString;
};

JSONIFY_METHOD(serializable)
{
	BEGIN_JSON_OBJ();
	WRITE_VARIABLE(test);
	WRITE_VARIABLE(anotherTest);
	WRITE_VARIABLE(someString);
	END_JSON_OBJ();
}

struct nested
{
	std::vector<serializable> test;
	int another;
};

JSONIFY_METHOD(nested)
{
	BEGIN_JSON_OBJ();
	WRITE_VARIABLE(test);
	WRITE_VARIABLE(another);
	END_JSON_OBJ();
}

int main(int argc, char** argv)
{
	serializable test;
	test.test = 30;
	test.anotherTest = 320.54032f;
	test.someString = "This is a test string, containing \"broken characters \n like these";

	nested nesttest;
	for (int i = 0; i < 10; ++i)
	{
		nesttest.test.push_back(test);
		nesttest.test[nesttest.test.size() - 1].test = 9 - i;
	}
	nesttest.another = -3;

	std::cout << autojson::JSON::stringify(test) << std::endl;
	std::cout << autojson::JSON::stringify(nesttest) << std::endl;

    return 0;
}