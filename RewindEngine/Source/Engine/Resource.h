/*
	FILE:			Resource.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/25/17
*/

/*
	Abstract Base Class for loading various resources
*/

#pragma once
#include <string>


class Resource 
{
public:

	//constructors/destructors
	Resource(size_t size, void * data, std::string const & type);
	~Resource();

	//getters
	void const * const & GetData() const;
	std::string const & GetType() const;
	
private:
	
	void *		m_data;
	std::string m_type;

};



