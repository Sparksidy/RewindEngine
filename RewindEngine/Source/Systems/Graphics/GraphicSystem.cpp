/*
File: GraphicSystem.cpp
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include <precompiled.h>

#include <Systems/Graphics/GraphicSystem.h>
#include <Systems/Graphics/CopyPostProcessor.h>
#include <Systems/Graphics/BloomPostProcessor.h>

#include <Systems/Core/GameObjectManager.h>
#include <Engine/Engine.h>
#include <Engine/GameObject.h>
#include <Engine/Component.h>
#include <Systems/Graphics/SpriteComponent.h>
#include <Systems/Graphics/AnimatedSpriteComponent.h>
#include <Systems/Core/TransformComponent.h>

#include <GL/glew.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

GraphicSystem::GraphicSystem(int const & width, int const & height) : m_width(width), m_height(height), m_defaultFramebuffer(width, height), m_pingFramebuffer(width, height), m_pongFramebuffer(width, height), m_renderer(), m_animationController(), m_postProcessorChain(), m_window(nullptr)
{

}


GraphicSystem::~GraphicSystem()
{

}

#pragma endregion

#pragma region "ISystem Methods"

bool GraphicSystem::Initialize()
{
	//create window
	m_window = new Window(800, 600, "rewind_engine");
	m_window->MakeCurrent();

	if (glewInit() != GLEW_OK)
	{
		//report error
		MessageBox(NULL, "Failed to initialize glew", "Error!", MB_OK | MB_ICONHAND);
		return false;
	}

	m_pingFramebuffer.CreateHandle();
	m_pongFramebuffer.CreateHandle();

	m_renderer.Initialize();
	m_renderer.SetProjectionMatrix(-(m_width/2), (m_width/2), (m_height/2), -(m_height/2));
	m_postProcessorChain.Initialize(new CopyPostProcessor());
	m_postProcessorChain.Append(new BloomPostProcessor());

	return (m_isInitialized = true);
}

void GraphicSystem::Update(float dt)
{
	static GameObjectManager * gameObjectManager = dynamic_cast<GameObjectManager*>(Engine::GetEngineSingleton().GetSystem("GameObjectManager"));
	
	//clear all framebuffers
	m_pingFramebuffer.ClearBuffers();
	m_pongFramebuffer.ClearBuffers();
	m_defaultFramebuffer.ClearBuffers();

	m_pingFramebuffer.Use();

	//render frame
	//probably have to traverse a scene graph and create a render queue

	for (auto gameObject : gameObjectManager->m_gameObjects)
	{
		if(!gameObject->GetActive())
			continue;

		Component * transform = gameObject->GetComponent(TRANSFORM_COMPONENT);
		if (transform)
		{
			Component * sprite = gameObject->GetComponent(SPRITE_COMPONENT);
			if (sprite)
			{
				m_renderer.RenderSprite(dynamic_cast<SpriteComponent&>(*sprite), 
					dynamic_cast<TransformComponent&>(*transform));
				continue;
			}
			sprite = gameObject->GetComponent(ANIMATED_SPRITE_COMPONENT);
			if (sprite)
			{
				AnimatedSpriteComponent & animated = dynamic_cast<AnimatedSpriteComponent&>(*sprite);
				m_renderer.RenderSprite(animated, dynamic_cast<TransformComponent&>(*transform));
				m_animationController.UpdateSprite(animated, dt);
				continue;
			}
		}
	}

	//apply post-processing effects
	m_postProcessorChain.Apply(m_defaultFramebuffer, &m_pingFramebuffer, &m_pongFramebuffer, m_renderer);

	//swap buffers
	m_window->SwapBuffers();
}

void GraphicSystem::Unload()
{
	m_postProcessorChain.Finalize();
	m_renderer.Finalize();
	m_pongFramebuffer.DestroyHandle();
	m_pingFramebuffer.DestroyHandle();
}

void GraphicSystem::ReceiveMessage(Message * msg)
{

}

std::string GraphicSystem::GetName() const
{
	return "Graphics";
}

void GraphicSystem::RegisterToLua(luabridge::lua_State* L)
{
	AnimatedSpriteComponent::RegisterToLua(L);
}

#pragma endregion

#pragma region "Public Methods"

void GraphicSystem::Resize(int const & newWidth, int const & newHeight)
{
	if (m_isInitialized)
	{
		m_width = newWidth;
		m_height = newHeight;
	}
}

void GraphicSystem::CommitResize()
{
	m_defaultFramebuffer.Use();
	m_defaultFramebuffer.Resize(m_width, m_height);
	m_pingFramebuffer.Resize(m_width, m_height);
	m_pongFramebuffer.Resize(m_width, m_height);
	m_renderer.SetProjectionMatrix(-(m_width / 2), (m_width / 2), (m_height / 2), -(m_height / 2));
}

#pragma endregion