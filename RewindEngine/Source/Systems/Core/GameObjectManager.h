/*
	FILE:			GameObjectManager.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/19/17
*/
#pragma once

#include <Systems\Core\ISystem.h>
#include <unordered_map>
#include <rapidjson/document.h>
#include <Engine\GameObject.h>


#include <list>

class GameObject;

typedef enum ARCHETYPENAME : unsigned int {

	//List the name of the archetype
	// Eg: ARCHETYPE_BULLET


}ARCHETYPENAME;


class GameObjectManager : public ISystem {
public:

	typedef rapidjson::GenericValue<rapidjson::UTF8<>>::Object JSONObject;

	//Constructors and Destructors
	GameObjectManager();
	~GameObjectManager();
	
	//Public Methods
	void LoadObject(JSONObject const & object);

	//ISystem Methods
	bool Initialize();
	void Update(float dt);
	void Unload();

	void ReceiveMessage(Message * msg);

	string GetName() const;

public:
	//List of all gameObjects
	std::vector<GameObject *> m_gameObjects;

	//List of archetypes
	std::map<ARCHETYPENAME, GameObject*> m_archetypesmap;

};

class Archetype
{
public:
	//Constructors/Destructors
	Archetype();
	~Archetype();

	//public methods
	GameObject* GetArchetype(ARCHETYPENAME name);

private:
	typedef rapidjson::GenericObject<false, rapidjson::GenericValue< rapidjson::UTF8<> > > JSONObject;

	//Creates an archetype with the archetype name and the json Object
	void CreateArchetype(ARCHETYPENAME name, JSONObject const & object);

};