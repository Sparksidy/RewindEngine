/*
	FILE:			ResourceLoader.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/25/17
*/

#pragma once

/*
	Abstract Base class for all resource loading
*/

class Resource;

class ResourceLoader
{
public:
	//constructors/destructors
	ResourceLoader() {};
	virtual ~ResourceLoader() {};

	//virtual public methods
	/*
		Creates a resource object, loads it and returns it so that it can be used by resource manager
	*/
	virtual Resource * LoadResource(std::string const & path) const = 0;
	virtual void Unload(Resource * resource) const = 0;
	virtual char const * ResourceType() const = 0;
	
private:
	

};
