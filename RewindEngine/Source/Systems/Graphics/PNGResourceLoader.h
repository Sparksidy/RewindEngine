#pragma once

#include <Systems\Core\ResourceLoader.h>

class PNGResourceLoader : public ResourceLoader
{
public:
	//constructores/destructor
	PNGResourceLoader();
	~PNGResourceLoader();

	//resource loader methods
	Resource * LoadResource(std::string const & path) const;
	void Unload(Resource * resource) const;
	char const * ResourceType() const;

};

