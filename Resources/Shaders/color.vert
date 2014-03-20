#version 130

in vec2 in_Position;
in vec4 in_Color;

out vec4 color;

uniform mat4 in_ProjectionMatrix;
uniform mat4 in_ViewMatrix;
uniform mat4 in_ModelMatrix;

void main()
{
	mat4 mvpMatrix = in_ProjectionMatrix * in_ViewMatrix * in_ModelMatrix;
	vec2 newPosition = mvpMatrix * in_Position;
	gl_Position = newPosition;

	color = in_Color;
}