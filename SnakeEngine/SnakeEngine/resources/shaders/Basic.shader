#shader vertex
#version 440 core

layout(location = 0) in vec4 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;
};


#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;
uniform vec3 dirLightPosition;
in vec3 Normal;
in vec3 FragPos;

void main()
{
	vec3 ambient = ambientLightStrength * ambientLightColor;
	vec3 result = ambient * vec3(u_Color.x,u_Color.y,u_Color.z);


	color = vec4(result,1.0);
};