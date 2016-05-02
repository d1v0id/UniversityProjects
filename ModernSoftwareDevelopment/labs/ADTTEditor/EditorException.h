#pragma once
class EditorException : public exception
{
public:
	EditorException(const char* s) : exception(s)
	{
	}
};