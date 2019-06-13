#include "FileException.h"



FileException::FileException(std::string errorThrown)
{
	m_error = errorThrown;
}

const char* FileException::what() const noexcept
{
	return m_error.c_str();
}

FileException::~FileException()
{
}
