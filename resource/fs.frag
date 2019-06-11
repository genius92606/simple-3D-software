#version 330
layout(location=0) out vec4 color;

uniform sampler2D text;
uniform vec3 object_color;
uniform int have_texture;

in vec3 v_position;
in vec2 v_uv;
in vec3 v_normal;

void main()
{

	vec3 light_pos=vec3(5.0,7.0,3.0);
	vec3 eye_pos=vec3(0.0, 0.0, 10.0);
	
	//Ambient light
	float ambientLight = 0.4;

	//Diffuse light
    vec3 lightDir = normalize(light_pos - v_position);
    vec3 n = normalize(v_normal);
    float diffuse = max(dot(lightDir, n), 0);  

	//specular light      //regular Phong shader
	vec3 reflectDir = reflect(-lightDir, n);
	vec3 eyeDir = normalize(eye_pos - v_position);
	float spec = pow(max(dot(eyeDir,reflectDir),0.0),8);

	


	if(have_texture==1)
	{
		color = vec4(vec3(1.0f,1.0f,1.0f)*texture(text, v_uv).rgb*(ambientLight+diffuse)+spec*vec3(0.8) , 1.0);
		//color = vec4(object_color, 1.0)*texture(text, uv);
	}		
	else{
		color = vec4(object_color*(ambientLight+diffuse)+spec*vec3(0.8) , 1.0);
	}
	
}