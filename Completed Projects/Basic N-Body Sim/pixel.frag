#version 430 core

// 0,0 is the bottom left corner
// 0,1 is the top left corner
// 1,0 is the bottom right corner
// 1,1 is the top right corner

out vec4 FragColor;

struct _vec2 { float x; float y; };
struct Color { float r; float g; float b; };
struct Body {
    _vec2 position;
    _vec2 velocity;
	Color color;
	float mass;
	bool collided;
};

layout(std430, binding = 0) buffer Bodies { Body bodies[]; };
uniform int bodyCount;

bool withinDist(float a, float b, float dist) {
	return abs(a-b) <= dist;
}

void main() {
    // Example: color pixel based on its position
	float x = gl_FragCoord.x / 1600;
	float y = gl_FragCoord.y / 900;
	
	int particleID = -1;
	bool isParticle = false;
	for (int i = 0; i < bodyCount; i++) {
		bool withinX = withinDist(bodies[i].position.x,x,0.001);
		bool withinY = withinDist(bodies[i].position.y,y,0.001);
		//bool withinBounds = (withinX && withinY) && (!bodies[i].collided);
		bool withinBounds = (withinX && withinY);
		isParticle = withinBounds || isParticle;
		if (withinBounds) { particleID = i; }
	}
	
	Color col = bodies[particleID].color;
	vec4 particleColor =   vec4(col.r,col.g,col.b,1);
	vec4 backgroundColor = vec4(0,0,0,1);
	
	float iPP = float(isParticle);
	FragColor = iPP*particleColor + (1-iPP)*backgroundColor;
}