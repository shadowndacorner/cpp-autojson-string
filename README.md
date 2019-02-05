# C++ Automated JSON Stringifier

This is a header-only library for quickly/nearly automatically converting C/C++ structs/classes into minified JSON.  It works through a set of macros which allow you to quickly define the JSON schema for an object, by simply marking which fields to write.

## Purpose

 I needed a simple library for quickly converting C/C++ data structures into JSON, but only one way.  Hence this library was born.

## Simple Example

The following is an example JSON definition for a simple datatype:
```c++
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
```

`JSONIFY_METHOD(typename)` generates the correct templated method name with preset variable names.  `BEGIN_JSON_OBJ()/END_JSON_OBJ()` mark the beginning and end of a single JSON object.  The calls to `WRITE_VARIABLE(variableName)` jsonify the target variable and name it correctly.  Sample stringification of this type might look like:

```c++
serializable test;
test.test = 30;
test.anotherTest = 320.54032f;
test.someString = "This is a test string, containing \"broken characters \n like these";
std::cout << autojson::JSON::stringify(test) << std::endl;
```

which outputs

```json
{"test":30,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"}
```

The library also supports nested objects in the same way.  For example:

```c++
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
// ...
nested nesttest;
for (int i = 0; i < 10; ++i)
{
    nesttest.test.push_back(test);
    nesttest.test[nesttest.test.size() - 1].test = 9 - i;
}
nesttest.another = -3;

std::cout << autojson::JSON::stringify(nesttest) << std::endl;
```
In the above example, nested stores a vector of serializable objects.  That yields the JSON string:
```JSON
{"test":[{"test":9,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":8,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":7,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":6,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":5,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":4,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":3,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":2,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":1,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"},{"test":0,"anotherTest":320.540314,"someString":"This is a test string, containing \u0022broken characters \u000a like these"}],"another":-3}
```
