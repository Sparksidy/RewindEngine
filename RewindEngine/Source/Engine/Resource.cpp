#include "precompiled.h"
#include "Resource.h"

Resource::Resource(size_t size, void * data, std::string const & type) : m_data(malloc(size)), m_type(type)
{
	memcpy_s(m_data, size, data, size);
}

Resource::~Resource()
{
	free(m_data);
}

void const * const & Resource::GetData() const
{
	return m_data;
}

std::string const & Resource::GetType() const
{
	return m_type;
}