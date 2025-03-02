#version 330 core
out vec4 FragColor;

in vec2 fragCoord;

uniform float zoom;
uniform vec2 center;
uniform int maxIterations;


void main() {

	vec2 normalisedC = (gl_FragCoord.xy / vec2(800.0, 800.0)- vec2(0.5));
	vec2 c = normalisedC * 4.0 * zoom + center;


	vec2 z = c;
	int i;

	//formula: Zn+1= Zn^2+C
	//sqaure of complex number : (x+yi)^2 = x^2 - y^2 + (2xy)i
	//z.x represents real part
	//z.y represents imaginary part

	for (i = 0; i < maxIterations; i++) {

		if (dot(z, z) > 4.0) {
			break;
		}
		else {
			z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
		}
	}

	float color = float(i) / float(maxIterations); 

	vec3 col = vec3(0.961 + 0.5 * cos(1.0 + color * 6.28318),  
                0.769 + 0.5 * cos(2.0 + color * 6.28318),  
                0.757 + 0.5 * cos(3.0 + color * 6.28318)); 

	FragColor = vec4(col, 1.0);

}
