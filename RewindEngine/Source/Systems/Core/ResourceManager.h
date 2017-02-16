/*
	FILE:			ResourceManager.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/25/17
*/
#pragma once

/*
	Central Factory for managing resources
*/

#include <Systems\Core\ISystem.h>

class Resource;
class ResourceLoader;

class ResourceManager : public ISystem
{
public:
	//Constructors/Destructors
	ResourceManager();
	virtual ~ResourceManager();

	//ISystem methods
	bool Initialize();
	void Update(float dt);
	void Unload();

	void ReceiveMessage(Message * msg);

	string GetName() const;
	
	//public methods
	void LoadResource(std::string const & path);
	void UnloadResource(Resource * resource);
	void Clear();
	
	//Getters/Setters
	const unsigned int GetResourceCount() const;
	Resource * GetResource(std::string const & path) const;

private:

	unsigned int m_resourceCount; //Total number of resources unloaded and loaded
	std::map<std::string, Resource *> m_resources; //List of resources 
	std::map<std::string, ResourceLoader *> m_loaders;

};
