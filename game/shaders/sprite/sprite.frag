#version 300 es
uniform sampler2D buffer;
in vec2 TexCoord;
out vec3 outColor;

void main(void) {
	outColor = texture(buffer, TexCoord).rgb;
}