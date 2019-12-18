#pragma once
#include <iostream>
#include <QtWidgets>
#include <array>

namespace SpaceInvaders {
	class Shaders {
	public:
		Shaders();
		virtual ~Shaders();
		void LoadShaders(QOpenGLContext* context);

		QOpenGLShaderProgram* GetSprite(void) const;
	private:
		QOpenGLShaderProgram* spriteShaderProgram;
	};
}