#include "stdafx.h"
#include "Person.h"


Person::Person(std::string first, std::string last, int age) : FirstName(first), LastName(last), Age(age)
{
}


Person::~Person(void)
{
}

http::json::value Person::ToJSON() const 
{
		http::json::value result = http::json::value::object();
		result[L"FirstName"] = http::json::value::string(utilities::conversions::to_string_t(FirstName));
		result[L"LastName"] = http::json::value::string(utilities::conversions::to_string_t(LastName));
		result[L"Age"] = http::json::value::number(Age);
        return result;
}
