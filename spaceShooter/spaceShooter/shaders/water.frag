

//varying vec3 Normal;
uniform vec3 ObjColor;
uniform samplerCube skybox;
varying vec3 norm;
varying vec3 viewVec;

void main () 
{
	  // Reflective ray (when hitting the object)
	vec3 ref = reflect(viewVec, norm);


	// Cube map lookup
	 gl_FragColor = texture(skybox, ref);
	// gl_FragColor = vec4(ObjColor,1.0);
}