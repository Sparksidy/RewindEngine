#pragma once

#define WIN32_LEAN_AND_MEAN	
#include <Windows.h>
#include <map>
#include <string>

#include <Utilities/GameClock.h>

//temporary forward declarations...
class ISystem;
class Message;

//modify these accordingly...
class Audio;
class GraphicSystem;
class Gameplay;
class PhysicsSystem;
class ScriptingEngine;
class GameObjectManager;


class Engine 
{
public:
	static Engine& GetEngineSingleton() { return *s_engineApp; }

	Engine();
	virtual ~Engine();

	virtual void AllocateSystems();
	virtual bool Initialize();
	virtual void Run();
	virtual void Unload();
	virtual void DeallocateSystems();
	virtual void SendMessageToSystems(Message* msg);

	bool IsRunning() const;
	LRESULT WINAPI MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	ISystem * GetSystem(std::string system);

	static void RegisterToLua(luabridge::lua_State* L);

private:
	static Engine* s_engineApp;

	void CalculateFrameTime(void);
	__int64 m_frameCount = 0;
	float m_timeElapsed = 0.0f;

	bool m_isPaused;
	bool m_isMinimized;
	bool m_isMaximized;
	bool m_isResized;
	bool m_isRunning;

	std::map<std::string, ISystem*> m_systems;
	GameClock m_gameClock;
};

