#version 400

in vec3 fvertex;
in vec4 fcolor;
in vec3 fnormal;
in vec2 ftexCoords;

in vec3 lightPos;

uniform int type;
uniform sampler2D tex;

uniform float Ka=1.0;
uniform float Kd=1.0;
uniform float Ks=1.0;
uniform float shininessVal=80;

// Material color
uniform vec3 ambientColor=vec3(.5, .5, .5);
uniform vec3 diffuseColor=vec3(.5, .5, .5);
uniform vec3 specularColor=vec3(.5, .5, .5);

void main() {
    if (type == 0)
        gl_FragColor = fcolor;
    else if (type == 2)
        gl_FragColor = fcolor * texture(tex, ftexCoords);
    
    else {
        vec3 N = normalize(fnormal);
        vec3 L = normalize(lightPos - fvertex);

        float lambertian = max(dot(N, L), 0.0);
        float specular = 0.0;
        if(lambertian > 0.0) {
            vec3 R = reflect(-L, N);
            vec3 V = normalize(-fvertex);

            float specAngle = max(dot(R, V), 0.0);
            specular = pow(specAngle, shininessVal);
        }

        vec4 color = vec4(Ka * ambientColor +
                          Kd * lambertian * diffuseColor +
                          Ks * specular * specularColor, 1.0);
        
        if (type == 1)
            gl_FragColor = color * fcolor;
        else if (type == 3)
		    gl_FragColor = color * fcolor * texture(tex, ftexCoords);
    }
}