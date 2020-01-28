#include <spaceinvaders/shaders.hpp>

using namespace SpaceInvaders;

Shaders::Shaders(QObject* parent) :
	spriteShaderProgram(new QOpenGLShaderProgram(parent))
{
	
}

Shaders::~Shaders() {
	if (spriteShaderProgram) {
		delete spriteShaderProgram;
	}
}

void Shaders::LoadShaders(QOpenGLContext* context) {
	if (spriteShaderProgram->hasOpenGLShaderPrograms(context->currentContext())) {
		spriteShaderProgram->addShaderFromSourceFile(
			QOpenGLShader::Vertex,
			":game/shaders/sprite/sprite.vert"
		);
		spriteShaderProgram->addShaderFromSourceFile(
			QOpenGLShader::Fragment,
			":game/shaders/sprite/sprite.frag"
		);
		spriteShaderProgram->link();
	}
}

QOpenGLShaderProgram* Shaders::GetSprite(void) const {
	return spriteShaderProgram;
}