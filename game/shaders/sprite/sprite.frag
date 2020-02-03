#version 300 es
uniform sampler2D buffer;
highp in vec2 TexCoord;
highp out vec3 outColor;

void main(void) {
	outColor = texture(buffer, TexCoord).rgb;
}