#version 330
layout(location=0) out vec4 color;

uniform sampler2D text;
uniform vec3 object_color;
uniform int have_texture;

in vec2 uv;

void main()
{
	if(have_texture==1)
	{
		color = vec4(object_color, 1.0)*texture(text, uv);
	}		
	else{
		color = vec4(object_color,1.0);
	}
	
}