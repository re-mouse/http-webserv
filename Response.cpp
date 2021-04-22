//
// Created by Holli Heimerdinger on 4/18/21.
//

#include "Response.hpp"

using namespace Http;

Response::Response(const string &http_version): response_status_code(200) /* server is broken */, http_version(http_version){}

Response * Response::code(unsigned int code)
{
	this->response_status_code = code;
	return this;
}

Response * Response::body(const string &body)
{
	this->response_body = body;
	return this;
}

Response * Response::putFile(const string &path)
{
	try {
		this->body(file_get_contents(path.substr(1)));
	} catch (exception e) {
		this->code(404);
	}
	return this;
}

Response *Response::header(const string & name, const string& value)
{
	this->headers[name] = value;
	return this;
}


string Http::get_code_message(unsigned int code)
{
	int size = sizeof(Http::codes) / sizeof(int);

	for (int i = 0; i < size; ++i)
	{
	if (Http::codes[i] == code)
	return Http::messages[i];
	}
	return "";
}



//string Http::get_mime_type(unsigned int code)
//{
//	int size = sizeof(Http::codes) / sizeof(int);
//
//	for (int i = 0; i < size; ++i)
//	{
//	if (Http::codes[i] == code)
//	return Http::messages[i];
//	}
//	return "";
//}


Response *Response::statusText(const string& name)
{
	this->response_status_text = name;
	return this;
}

string Response::toString()
{
	string message;

	// make first string (ex. "HTTP/1.1 200 OK")
	message = "HTTP/" + this->http_version + " " + to_string(this->response_status_code) + " ";

	if (!this->response_status_text.empty())
		message += this->response_status_text;
	else
		message += get_code_message(this->response_status_code);
	message += "\n";

	// insert headers
	map<string, string>::iterator begin = headers.begin();
	map<string, string>::iterator end = headers.end();
	while (begin != end)
	{
		message += begin->first + ": " + begin->second + "\n";
		begin++;
	}
	if (headers.count("Content-Length") == 0) {
		message += "Content-Length: " + to_string(this->response_body.length()) + "\n";
	}
	if (headers.count("Content-Type") == 0) {
		message += "Content-Type: text/plain\n";
	}

	message += "\n" + this->response_body;

	return message;
}

Response &Response::operator=(const Response &rhs)
{
	if (this != &rhs)
	{
		this->headers = rhs.headers;
		this->http_version = rhs.http_version;
		this->response_body = rhs.response_body;
		this->response_status_code = rhs.response_status_code;
		this->response_status_text = rhs.response_status_text;
	}
	return *this;
}

Response::~Response()
{

}

Response::Response(const Response &rhs)
{
	operator=(rhs);
}

