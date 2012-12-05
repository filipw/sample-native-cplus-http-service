// NativeHttpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "astreambuf.h"
#include "Person.h"

using namespace http;
using namespace http::listener;

int _tmain(int argc, _TCHAR* argv[])
{
	uri_builder uri(L"http://localhost:4999/");
	http_listener listener;
	auto p = new Person("Filip","W",95);

	    listener = http_listener::create(uri.to_uri(),
        [p](http_request message)
        {
			std::cout << "Serving GET" << std::endl;
			message.reply(http::status_codes::OK, p->ToJSON());
        },
        [p](http_request message)
        {
			auto posted = p->FromJSON(message.extract_json().get());
			message.reply(http::status_codes::NoContent);
			std::cout << "Received a PUT of " << posted.FirstName << ", " << posted.LastName << ", " << posted.Age << std::endl;
        },
        [p](http_request message)
        {
			auto posted = p->FromJSON(message.extract_json().get());
			std::cout << "Received a POST of " << posted.FirstName << ", " << posted.LastName << ", " << posted.Age << std::endl;
			message.reply(http::status_codes::NoContent);
        },
        [p](http_request message)
        {
			message.reply(http::status_codes::NoContent);
			std::cout << "Deleting " << p->FirstName << std::endl;
        });

		listener.listen([]() { fgetc(stdin); }).wait();

	return 0;
}

