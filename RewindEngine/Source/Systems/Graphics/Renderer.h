/*
File:Renderer.h
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include <Utilities\math\mat3.h>
#include <Utilities\math\mat4.h>
#include <Utilities\math\vec3.h>
#include <Utilities\math\vec2.h>

#include "Program.h"

class TransformComponent;

namespace Graphics
{

	class SpriteComponent;
	class AnimatedSpriteComponent;

	class Renderer
	{
	public:

		//constructors/destructor
		Renderer();
		~Renderer();

		//public methods
		void Initialize();
		void Finalize();

		void ClearBuffers();

		void RenderSprite(SpriteComponent const & sprite, TransformComponent const & transform);
		void RenderSprite(AnimatedSpriteComponent const & sprite, TransformComponent const & transform);

		void RenderScreenQuad(Program & program);

		//getters
		math::mat4<> const & GetProjectionMatrix() const;
		math::mat4<> const & GetViewMatrix() const;

		//setters
		void SetProjectionMatrix(int const & left, int const & right, int const & top, int const & bottom);
		void SetViewMatrix(math::mat4<float> const & view);


		void SetClearColor(float const & r, float const & g, float const & b, float const & a);

	private:

		static math::mat4<> ConstructTransformMatrix(TransformComponent const & transform);

		//private methods
		void RenderQuad();


		Program m_program;

		unsigned int m_quadVAO;
		unsigned int m_quadVBO;

		//attributes
		math::mat4<float> m_projectionMatrix;
		math::mat4<float> m_viewMatrix;

	};

}