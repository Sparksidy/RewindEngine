/*
File: GraphicSystem.h
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include <Systems/Graphics/Renderer.h>
#include <Systems/Graphics/PostProcessorChain.h>
#include <Systems/Graphics/Framebuffer.h>
#include <Systems/Graphics/DefaultFramebuffer.h>
#include <Systems/Graphics/Window.h>
#include <Systems/Graphics/AnimationController.h>

#include <Systems/Core/ISystem.h>

class GraphicSystem : public ISystem
{

public:
	
	//constructors/destructor
	GraphicSystem(int const & width, int const & height);
	virtual ~GraphicSystem();

	//ISystem Methods
	bool Initialize();
	void Update(float dt);
	void Unload();

	void ReceiveMessage(Message * msg);

	std::string GetName() const;

	static void RegisterToLua(luabridge::lua_State* L);

	//public methods
	void Resize(int const & newWidth, int const & newHeight);
	void CommitResize();

private:

	int m_width;
	int m_height;

	Graphics::DefaultFramebuffer m_defaultFramebuffer;
	Graphics::Framebuffer m_pingFramebuffer;
	Graphics::Framebuffer m_pongFramebuffer;

	Graphics::Renderer m_renderer;
	Graphics::AnimationController m_animationController;
	Graphics::PostProcessorChain m_postProcessorChain;
	Graphics::Window * m_window;

};

