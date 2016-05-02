#pragma once
class CalcException : public exception
{
public:
	CalcException(const char* s) : exception(s)
	{
	}
};