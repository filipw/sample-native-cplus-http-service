#pragma once
class Person
{
public:
	std::string FirstName;
	std::string LastName;
	int Age;

	http::json::value ToJSON() const;
	Person(std::string first, std::string last, int age);
	~Person(void);

	static Person FromJSON(http::json::value object)
    {
        const http::json::value &first = object[L"FirstName"];
        const http::json::value &last = object[L"LastName"];
        const http::json::value &age = object[L"Age"];

		Person result(utilities::conversions::to_utf8string(first.as_string()), utilities::conversions::to_utf8string(last.as_string()), age.as_integer());
        return result;
    }
};

