#pragma once
#include <QtWidgets>
#include <array>
#include <iostream>

namespace SpaceInvaders {
	class Shaders {
	public:
		Shaders(QObject* parent);
		virtual ~Shaders();
		void LoadShaders(QOpenGLContext* context);

		QOpenGLShaderProgram* GetSprite(void) const;
	private:
		QOpenGLShaderProgram* spriteShaderProgram;
	};
}