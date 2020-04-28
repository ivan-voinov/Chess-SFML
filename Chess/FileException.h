#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
private:
	std::string m_error;

public:
	FileException(std::string errorThrown);
	const char* what() const noexcept;
	~FileException();
};

