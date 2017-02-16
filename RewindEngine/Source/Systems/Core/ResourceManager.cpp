#include <precompiled.h>
#include <Systems\Core\ResourceManager.h>
#include <Systems\Core\ResourceLoader.h>
#include <Systems\Graphics\PNGResourceLoader.h>
#include <Engine\Resource.h>

#include <Shlwapi.h>
#include <functional>


#pragma region "Constructors/Destructor"

ResourceManager::ResourceManager() :  m_resourceCount(0)
{
}

ResourceManager::~ResourceManager()
{
	Clear();
}

#pragma endregion

#pragma region "Public Methods"

void ResourceManager::LoadResource(std::string const & path)
{
	//has this resource been loaded previously?
	if (m_resources.count(path))
		return;

	std::string extension(PathFindExtension(path.c_str()));

	//do we know how to load it?
	if (m_loaders.count(extension) > 0)
	{
		//load it
		Resource * resource = m_loaders[extension]->LoadResource(path);
		if (resource)
			m_resources[path] = resource;
	}
}

void ResourceManager::UnloadResource(Resource * resource)
{
	m_loaders[resource->GetType()]->Unload(resource);
}

void ResourceManager::Clear()
{
	for (auto iterator = m_resources.begin(); iterator != m_resources.end(); ++iterator)
	{
		UnloadResource(iterator->second);
		delete iterator->second;
	}
	m_resources.clear();
	m_resourceCount = 0;
}

#pragma endregion

#pragma region "Getters/Setters"

Resource * ResourceManager::GetResource(std::string const & path) const
{
	//if resource has been load, retrieve it
	if (m_resources.count(path))
		return m_resources.at(path);
	return nullptr;
}

const unsigned int ResourceManager::GetResourceCount() const
{
	return m_resourceCount;
}


#pragma endregion

#pragma region "ISystem Methods"

bool ResourceManager::Initialize()
{
	PNGResourceLoader * pngLoader = new PNGResourceLoader();
	m_loaders[pngLoader->ResourceType()] = pngLoader;
	return true;
}

void ResourceManager::Update(float dt)
{

}

void ResourceManager::Unload()
{
	Clear();
	for (auto loaders : m_loaders)
		delete loaders.second;
	m_loaders.clear();
}

void ResourceManager::ReceiveMessage(Message * msg)
{

}

string ResourceManager::GetName() const
{
	return "ResourceManager";
}

#pragma endregion