#version 130

in vec2 texCoords;
in vec4 color;
uniform sampler2D in_Texture;

out vec4 out_Color;

void main()
{
	out_Color = color * texture(in_Texture, texCoords);
}
