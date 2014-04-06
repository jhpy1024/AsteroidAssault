#version 130

in vec2 in_Position;
in vec2 in_TexCoords;
in vec4 in_Color;

out vec2 texCoords;
out vec4 color;

uniform mat4 in_ProjectionMatrix;
uniform mat4 in_ViewMatrix;
uniform mat4 in_ModelMatrix;

void main()
{
	mat4 mvpMatrix = in_ProjectionMatrix * in_ViewMatrix * in_ModelMatrix;
	vec4 newPosition = mvpMatrix * vec4(in_Position, 0.0, 1.0);
	gl_Position = newPosition;

	texCoords = in_TexCoords;
	color = in_Color;
}