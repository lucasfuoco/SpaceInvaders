#version 300 es
uniform sampler2D buffer;
in highp vec2 TexCoord;
out highp vec3 outColor;

void main(void) {
	outColor = texture(buffer, TexCoord).rgb;
}