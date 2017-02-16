#include <precompiled.h>

/*
File: Renderer.cpp
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/


#include <Systems/Graphics/Renderer.h>
#include <Systems/Graphics/Program.h>

#include <Systems/Core/TransformComponent.h>
#include <Systems/Graphics/SpriteComponent.h>
#include <Systems/Graphics/AnimatedSpriteComponent.h>

#include <Engine/Resource.h>

#include <GL/glew.h>


using namespace Graphics;

#pragma region "Static Data and Functions"

math::mat4<> Renderer::ConstructTransformMatrix(TransformComponent const & transform)
{
	const math::vec2<> t = transform.GetTranslation();
	const math::vec2<> s = transform.GetScale();
	return math::mat4<>::translate(t.x, t.y, 0) * 
		math::mat4<>::scale(s.x, s.y, 1.0f) * 
		math::mat4<>::rotateByDegree(transform.GetRotation());
}

#pragma endregion

#pragma region "Constructors/Destructor"

Renderer::Renderer() : m_program(), m_quadVAO(0), m_quadVBO(0), m_projectionMatrix(), m_viewMatrix()
{

}


Renderer::~Renderer()
{

}

#pragma endregion

#pragma region "Public Methods"

void Renderer::Initialize()
{
	//create program
	m_program.CreateHandle();
	m_program.AttachShader(Program::VERTEX_SHADER_TYPE, "Source/Systems/Graphics/Shaders/Generic.vert");
	m_program.AttachShader(Program::FRAGMENT_SHADER_TYPE, "Source/Systems/Graphics/Shaders/Generic.frag");
	m_program.Link();

	glGenVertexArrays(1, &m_quadVAO);
	glBindVertexArray(m_quadVAO);

	float quadVertices[] = {
		-0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	glGenBuffers(1, &m_quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(float) * 2));

	glBindVertexArray(0);

	m_program.SetUniform("projectionMatrix", m_projectionMatrix);
	m_program.SetUniform("viewMatrix", m_viewMatrix);
	m_program.SetUniform("transformMatrix", math::mat4<>());
	m_program.SetUniform("sampler", 0);

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Finalize()
{
	m_program.DestroyHandle();

	glDeleteBuffers(1, &m_quadVBO);
	glDeleteVertexArrays(1, &m_quadVAO);
}

void Renderer::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderSprite(SpriteComponent const & sprite, TransformComponent const & transform)
{
	m_program.SetUniform("mode", 1);
	m_program.SetUniform("transformMatrix", ConstructTransformMatrix(transform));
	
	m_program.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *((GLuint*)sprite.GetTexture()->GetData()));

	RenderQuad();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_program.Unuse();
}

void Renderer::RenderSprite(AnimatedSpriteComponent const & sprite, TransformComponent const & transform)
{
	m_program.SetUniform("mode", 2);
	m_program.SetUniform("transformMatrix", ConstructTransformMatrix(transform));

	//construct texture matrix
	math::vec2<float> const & scale = sprite.GetFrameSize();
	float x, y;

	switch (sprite.GetType())
	{
		case AnimatedSpriteComponent::COLUMN_SPRITE_SHEET:
			x = (float)(sprite.GetCurrentFrame() / sprite.GetFramesPerElement()) * scale.x;
			y = 1.0f - ((float)(((sprite.GetCurrentFrame() % sprite.GetFramesPerElement())) + 1) * scale.y);
			break;
		case AnimatedSpriteComponent::ROW_SPRITE_SHEET:
			x = (float)(sprite.GetCurrentFrame() % sprite.GetFramesPerElement()) * scale.x;
			y = 1.0f - ((float)(((sprite.GetCurrentFrame() / sprite.GetFramesPerElement())) + 1) * scale.y);
			break;
	}

	math::mat3<float> textureMatrix;
	textureMatrix.m[0][0] = scale.x;	textureMatrix.m[0][1] = 0;			textureMatrix.m[0][2] = x;
	textureMatrix.m[1][0] = 0;			textureMatrix.m[1][1] = scale.y;	textureMatrix.m[1][2] = y;
	textureMatrix.m[2][0] = 0;			textureMatrix.m[2][1] = 0;			textureMatrix.m[2][2] = 1;
	m_program.SetUniform("textureMatrix", textureMatrix);

	m_program.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *((GLuint*)sprite.GetSpriteSheet()->GetData()));

	RenderQuad();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_program.Unuse();
}

void Renderer::RenderScreenQuad(Program & program)
{
	program.SetUniform("transformMatrix", math::mat4<float>::scale(2.0f, 2.0f, 1.0f));
	program.Use();
	RenderQuad();
	program.Unuse();
}

#pragma endregion

#pragma region "Getters"

math::mat4<float> const & Renderer::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

math::mat4<float> const & Renderer::GetViewMatrix() const
{
	return m_viewMatrix;
}

#pragma endregion

#pragma region "Setters"

void Renderer::SetProjectionMatrix(int const & left, int const & right, int const & top, int const & bottom)
{
	m_projectionMatrix.m[0][0] = 2.0f / (float)(right - left);
	m_projectionMatrix.m[0][3] = -(float)(right + left) / (float)(right - left);
	m_projectionMatrix.m[1][1] = 2.0f / (float)(top - bottom);
	m_projectionMatrix.m[1][3] = -(float)(top + bottom) / (float)(top - bottom);
	m_projectionMatrix.m[2][2] = -1.0f;
	m_projectionMatrix.m[2][3] = 0;
	m_program.SetUniform("projectionMatrix", m_projectionMatrix);
}

void Renderer::SetViewMatrix(math::mat4<float> const & viewMatrix)
{
	m_viewMatrix = viewMatrix;
	m_program.SetUniform("viewMatrix", m_viewMatrix);
}

void Renderer::SetClearColor(float const & r, float const & g, float const & b, float const & a)
{
	glClearColor(r, g, b, a);
}

#pragma endregion

#pragma region "Private Methods"

void Renderer::RenderQuad()
{
	glBindVertexArray(m_quadVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

#pragma endregion