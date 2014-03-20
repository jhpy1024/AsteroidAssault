#version 130

in vec2 texCoords;
uniform sampler2D in_Texture;

out vec4 out_Color;

void main()
{
	out_Color = texture(in_Texture, texCoords);
}
