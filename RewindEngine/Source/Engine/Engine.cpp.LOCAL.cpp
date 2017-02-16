#include <precompiled.h>
#include <windowsx.h>
#include <Systems/Core/ISystem.h>
#include <Engine/Engine.h>

#include <Systems/Input/Input.h>
#include <Systems/Graphics/GraphicSystem.h>
#include <Systems/Core/GameObjectManager.h>
#include <Systems/Physics/PhysicsSystem.h>
#include <Systems/Core/ResourceManager.h>
#include <Systems/Core/LevelManager.h>
#include <Systems/Scripting/ScriptingManager/ScriptingManager.h>

#include <Utilities/Math/LuaMathHelper.h>
#include <Systems/Core/TransformComponent.h>





/* include all of the system files here*/

Engine* Engine::s_engineApp = nullptr;



Engine::Engine():
	m_isPaused(false),
	m_isMinimized(false),
	m_isMaximized(false),
	m_isResized(false),
	m_isRunning(false)
{
	//assert(s_engineApp == nullptr);
	s_engineApp = this;
}

Engine::~Engine()
{

}

void Engine::AllocateSystems()
{
	ISystem * graphics = new GraphicSystem(800, 600);
	if (graphics)
		m_systems[graphics->GetName()] = graphics;

	ISystem * gameObjectManager = new GameObjectManager();
	if (gameObjectManager)
		m_systems[gameObjectManager->GetName()] = gameObjectManager;

	ISystem * resourceManager = new ResourceManager();
	if (resourceManager)
		m_systems[resourceManager->GetName()] = resourceManager;

	ISystem * levelManager = new LevelManager();
	if (levelManager);
		m_systems[levelManager->GetName()] = levelManager;

	ISystem* scriptManager = new ScriptingManager();
	if (scriptManager)
		m_systems[scriptManager->GetName()] = scriptManager;
	ISystem * physics = new PhysicsSystem();
	if (physics)
		m_systems[physics->GetName()] = physics;
}

bool Engine::Initialize()
{
	//Initialize all of the systems
	for (auto system : m_systems)
		if (!system.second->Initialize())
			return m_isRunning = false;

	LevelManager * levelManager = dynamic_cast<LevelManager*>(GetSystem("LevelManager"));
	levelManager->LoadLevel("Resources/Levels/DemoLevel.json");

	return m_isRunning = true;
}

void Engine::Run()
{
	MSG msg = { 0 };

	m_gameClock.ResetClock();


	
	while (IsRunning())
	{
		// If there are Window messages then process them.
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
			}
		}
		if (m_gameClock.GetDeltaTime() < 0.0166666666667f)
		{
			//sleep the thread for a little bit
			int waitTimeMS = (int)((0.0166666666667f - m_gameClock.GetDeltaTime()) * 1000.0f);
			Sleep(waitTimeMS);
		}

		// Otherwise, do animation/game stuff.
		m_gameClock.Tick();

		if (!m_isPaused)
		{
			CalculateFrameTime();
			for(auto system : m_systems)
				system.second->Update(m_gameClock.GetDeltaTime());

		}
		else
		{
			//sleep the thread for a little bit
			Sleep(100);
		}

	} // end while(IsRunning())
}

void Engine::Unload()
{
	//Initialize all of the systems
	for (auto system : m_systems)
		system.second->Unload();
}

void Engine::DeallocateSystems()
{
	//Initialize all of the systems
	for (auto system : m_systems)
		SafeDelete(system.second);

	m_systems.clear();
}

void Engine::SendMessageToSystems(Message* msg)
{
	for (auto system : m_systems)
		system.second->ReceiveMessage(msg);
}

bool Engine::IsRunning() const
{
	return m_isRunning;
}

LRESULT WINAPI Engine::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//handle input for the application
	switch (msg)
	{
	case WM_SIZE:
	{
		unsigned newWidth = LOWORD(lParam);
		unsigned newHeight = HIWORD(lParam);
		/*
		Update graphics and window with these new sizes...
		*/

		return 0;
	}

	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			//m_IsPaused = true;
			m_gameClock.StopClock();
		}
		else
		{
			//m_IsPaused = false;
			m_gameClock.StartClock();
		}
		return 0;

	case WM_ENTERSIZEMOVE:
		m_isPaused = true;
		m_isResized = true;
		m_gameClock.StopClock();
		return 0;

	case WM_EXITSIZEMOVE:
		m_isPaused = false;
		m_isResized = false;
		m_gameClock.StartClock();
		//mGFXSys->OnResize();
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		Input::MouseEvent::SetLeftMouseButton(true);
		break;
	case WM_MBUTTONDOWN:
		Input::MouseEvent::SetMiddleMouseButton(true);
		break;
	case WM_RBUTTONDOWN:
		Input::MouseEvent::SetRightMouseButton(true);
		break;
	case WM_LBUTTONUP:
		Input::MouseEvent::SetLeftMouseButton(false);
		break;
	case WM_MBUTTONUP:
		Input::MouseEvent::SetMiddleMouseButton(false);
		break;
	case WM_RBUTTONUP:
		Input::MouseEvent::SetRightMouseButton(false);
		break;
	case WM_MOUSEMOVE:
		Input::MouseEvent::SetMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_KEYUP:
		Input::KeyboardEvent::SetKey(wParam, false);
		break;

	case WM_KEYDOWN:
	{
		Input::KeyboardEvent::SetKey(wParam, true);
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Engine::CalculateFrameTime(void)
{
	m_frameCount++;

	// Compute averages over one second period.
	if ((m_gameClock.GetTotalTime() - m_timeElapsed) >= 1.0f)
	{
		float fps = (float)m_frameCount; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		// Reset for next average.
		m_frameCount = 0;
		m_timeElapsed += 1.0f;
	}
}

ISystem * Engine::GetSystem(string system)
{
	if (m_systems.count(system))
		return m_systems[system];
	else
		return nullptr;
}

void Engine::RegisterToLua(luabridge::lua_State* L)
{
	//Utilities...
	math::LuaMathHelper::RegisterToLua(L);

	//Systems...
	Input::InputHandler::RegisterToLua(L);
	GraphicSystem::RegisterToLua(L);
	PhysicsSystem::RegisterToLua(L);
	/*
		std::map<string, ISystem*>::iterator it = m_systems.find("Physics");
	getGlobalNamespace(L)
		.beginNamespace("GlobalPhysics")
			.addVariable<PhysicsSystem>("system",  (PhysicsSystem*)( )
		.endNamespace();
	*/

	//Components...
	TransformComponent::RegisterToLua(L);

	//GameObjects...
	GameObject::RegisterToLua(L);
}