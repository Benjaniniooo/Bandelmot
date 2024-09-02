const char* vertexShaderProg = R"(
#version 460 core
layout (location = 0) in vec3 pos;

out vec2 positionVertex;

void main(){
    gl_Position = vec4(pos, 1.0);
    positionVertex = pos.xy;
}
)";

const char* fragmentShaderProg = R"(
#version 460 core
in vec2 positionVertex;

out vec4 color;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(){
    vec2 c = vec2(
        map(positionVertex.x, -1.0, 1.0, -2.0, 2.0),
        map(positionVertex.y, -1.0, 1.0, -2.0, 2.0)
        );

    vec2 z = vec2(0.0, 0.0);

    uint iterationMax = 100;

    uint iteration = 0;

    while(length(z) <= 8 && iteration < iterationMax){
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y);
        z = z + c;

        iteration = iteration + 1;
    }

    float grad = map(iteration, 0, iterationMax, 0.0, 1.0);

    color = vec4(grad, grad, grad, 1.0);
}
)";

GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f, 1.0f, 0.0f,  // top left
    1.0f, 1.0f, 0.0f,   // top right
    1.0f, -1.0f, 0.0f,  // bottom right
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};