#version 130

in vec2 in_Position;
in vec2 in_TexCoords;

out vec2 texCoords;

uniform mat4 in_ProjectionMatrix;
uniform mat4 in_ViewMatrix;
uniform mat4 in_ModelMatrix;

uniform float in_Time;

uniform int in_CameraShakeEnabled;
uniform float in_CameraShakeAmount;

void main()
{
	mat4 newViewMatrix = in_ViewMatrix;

	if (in_CameraShakeEnabled == 1)
	{
		newViewMatrix[3][0] += cos((in_Time / 3.0) * 2 * 3.14159) * in_CameraShakeAmount;
		newViewMatrix[3][1] += sin((in_Time / 3.0) * 2 * 3.14159) * in_CameraShakeAmount;
	}
		
	mat4 mvpMatrix = in_ProjectionMatrix * newViewMatrix * in_ModelMatrix;
	vec4 newPosition = mvpMatrix * vec4(in_Position, 0.0, 1.0);
	gl_Position = newPosition;

	texCoords = in_TexCoords;
}