
varying vec3 Normal;
varying vec2 texCoord;
uniform sampler2D height;

void main()
{
	texCoord = gl_MultiTexCoord0.xy;
    gl_FrontColor = gl_Color;
	vec4 pos = gl_Vertex;
	pos.y = (texture2D(height, texCoord)*1000.0).x-1000.0;
	pos.x *= 6.0;
    gl_Position = gl_ModelViewProjectionMatrix * pos;
}

