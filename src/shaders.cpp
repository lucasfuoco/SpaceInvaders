#include <shaders.hpp>

using namespace SpaceInvaders;

Shaders::Shaders() :
	spriteShaderProgram(new QOpenGLShaderProgram())
{
	
}

Shaders::~Shaders() {

}

void Shaders::LoadShaders(QOpenGLContext* context) {
	spriteShaderProgram->setParent(context);
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

QOpenGLShaderProgram* Shaders::GetSprite(void) const {
	return spriteShaderProgram;
}