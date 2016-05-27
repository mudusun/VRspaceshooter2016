/* Vertex shader */
uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;

varying vec3 norm;
varying vec3 viewVec;
 
void main(void)
{

	vec4 v = vec4(gl_Vertex);
	v.y = sin(waveWidth * v.x + waveTime) * cos(waveWidth * v.y + waveTime) * waveHeight;
	gl_Position = gl_ModelViewProjectionMatrix * v;

	
	vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    norm      = normalize(gl_NormalMatrix * gl_Normal);
    viewVec    = normalize(-ecPosition);
   // gl_Position     = ftransform();
   // gl_TexCoord[0] = gl_MultiTexCoord0;
}