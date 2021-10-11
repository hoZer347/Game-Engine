#version 400

in vec3 fvertex;
in vec4 fcolor;
in vec3 fnormal;
in vec2 ftexCoords;

uniform sampler2D tex;
uniform bool type;

//void main() {
//	if (type)
//		gl_FragColor = texture2D(tex, ftexCoords);
//	else
//		gl_FragColor = fcolor;
//};

uniform int mode=0;   // Rendering mode
uniform float Ka=1.0;   // Ambient reflection coefficient
uniform float Kd=1.0;   // Diffuse reflection coefficient
uniform float Ks=1.0;   // Specular reflection coefficient
uniform float shininessVal=80; // Shininess

// Material color
uniform vec3 ambientColor=vec3(1, 1, 1);
uniform vec3 diffuseColor=vec3(1, 1, 1);
uniform vec3 specularColor=vec3(1, 1, 1);
uniform vec3 lightPos=vec3(100, 100, 100); // Light position

void main() {
    vec3 N = normalize(fnormal);
    vec3 L = normalize(lightPos - fvertex);

    // Lambert's cosine law
    float lambertian = max(dot(N, L), 0.0);
    float specular = 0.0;
    if(lambertian > 0.0) {
        vec3 R = reflect(-L, N);      // Reflected light vector
        vec3 V = normalize(-fvertex); // Vector to viewer
        // Compute the specular term
        float specAngle = max(dot(R, V), 0.0);
        specular = pow(specAngle, shininessVal);
    }
    vec4 color = vec4(Ka * ambientColor +
                      Kd * lambertian * diffuseColor +
                      Ks * specular * specularColor, 1.0);

   	if (type)
		gl_FragColor = texture2D(tex, ftexCoords);
	else
		gl_FragColor = fcolor;
}