/*
File: Program.h
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include <Utilities\math\mat4.h>
#include <Utilities\math\mat3.h>
#include <Utilities\math\vec2.h>
#include <Utilities\math\vec3.h>

namespace Graphics
{

	class Program
	{
	public:

		typedef enum ShaderType {
			VERTEX_SHADER_TYPE = 0x8B31,
			FRAGMENT_SHADER_TYPE = 0x8B30
		} ShaderType;

		//constructors/destructor
		Program();
		~Program();

		//public methods
		void Use();
		void Unuse();
		
		void SetUniform(char const * name, math::mat4<float> const & matrix);
		void SetUniform(char const * name, math::mat3<float> const & matrix);
		void SetUniform(char const * name, math::vec3<float> const & vector);
		void SetUniform(char const * name, math::vec2<float> const & vector);
		void SetUniform(char const * name, float const & value);
		void SetUniform(char const * name, int const & value);

		void CreateHandle();
		void DestroyHandle();
		void AttachShader(ShaderType const & type, char const * path);
		void Link();


	private:

		unsigned int m_handle;

	};

}