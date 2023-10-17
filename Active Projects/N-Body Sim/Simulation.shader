#version 430 // You need version 430 for compute shaders

float minimumCollisionDistance = 0.00001;
float G = 0.0000000000667430;
layout (local_size_x = 256) in; // define work group size

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

void main() {
    uint idx = gl_GlobalInvocationID.x;

    for (int i = 0; i < bodies.length(); i++) {
		float sameIndex = (i == idx) ? 1.0 : 0.0;
		
		float xDiff = bodies[i].position.x - bodies[idx].position.x;
		float yDiff = bodies[i].position.y - bodies[idx].position.y;
		float distSquared = xDiff*xDiff + yDiff*yDiff;
		
		//Calculate the gravitational force
		float force = G * bodies[i].mass * bodies[idx].mass / (distSquared + sameIndex);
		
		//Calculate the direction of the force
		float dist = sqrt(distSquared);
		float unitX = xDiff / (dist + sameIndex); // unit vector x-component
        float unitY = yDiff / (dist + sameIndex); // unit vector y-component
        float xForce = force * unitX;
        float yForce = force * unitY;
		
		//Apply forces
		bodies[idx].velocity.x += xForce*(1-sameIndex);
		bodies[idx].velocity.y += yForce*(1-sameIndex);
		
		// Calculate collisions
		//bool hasCollided = false;//dist <= minimumCollisionDistance;
		//bool biggerBody = bodies[idx].mass > bodies[i].mass;
		//bool sameMass = bodies[idx].mass == bodies[i].mass;
		//biggerBody = biggerBody || (sameMass && (idx > i));
		
		//bodies[idx].collided = bodies[idx].collided || ((!biggerBody) && hasCollided);
		//bodies[idx].mass = bodies[idx].mass * float(!hasCollided || (hasCollided && biggerBody));
		
		//bodies[i].collided = bodies[i].collided || (biggerBody && hasCollided);
		//bodies[i].mass = bodies[i].mass * float(!hasCollided || (hasCollided && (!biggerBody)));
		
	}
	
	bodies[idx].position.x += bodies[idx].velocity.x;
	bodies[idx].position.y += bodies[idx].velocity.y;
}
