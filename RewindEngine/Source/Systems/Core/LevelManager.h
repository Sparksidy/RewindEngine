#pragma once

#include <Systems\Core\ISystem.h>

class LevelManager : public ISystem
{
public:
	
	//constructors/destructor
	LevelManager();
	~LevelManager();

	//ISystem methods
	bool Initialize();
	void Update(float dt);
	void Unload();

	void ReceiveMessage(Message * msg);

	string GetName() const;

	//public methods
	void LoadLevel(char const * levelFile);

};

