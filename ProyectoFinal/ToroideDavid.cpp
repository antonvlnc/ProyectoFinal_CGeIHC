
#include "ToroideDavid.h"

ToroideDavid::ToroideDavid() {

    R = 1.0f;
    r = 0.5f;

    numMinorSegments = 10;
    numMajorSegments = 20;

    vao = 0;
    vboVertices = 0;

    vertexCount = 0;

}

ToroideDavid::ToroideDavid(float inRadius, float outRadius, int nSides, int nRings) {

	R = inRadius;
	r = outRadius;

    numMinorSegments = nSides;
    numMajorSegments = nRings;

	vao = 0;
	vboVertices = 0;

    vertexCount = 0;

}


void ToroideDavid::generateTorus() {

    std::vector<GLfloat> vertices;

    // Para cada segmento mayor
    for (int i = 0; i <= numMajorSegments; ++i) {
        float theta = 2.0f * 3.1416f * i / numMajorSegments;
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);

        // Para cada segmento menor
        for (int j = 0; j <= numMinorSegments; ++j) {
            float phi = 2.0f * 3.1416f * j / numMinorSegments;
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            // Coordenadas de los vértices
            float x = (R + r * cosPhi) * cosTheta;
            float y = (R + r * cosPhi) * sinTheta;
            float z = r * sinPhi;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Coordenadas del siguiente vértice
            float nextTheta = 2.0f * 3.1416f * (i + 1) / numMajorSegments;
            float nextCosTheta = cos(nextTheta);
            float nextSinTheta = sin(nextTheta);

            float nextX = (R + r * cosPhi) * nextCosTheta;
            float nextY = (R + r * cosPhi) * nextSinTheta;
            float nextZ = z;

            vertices.push_back(nextX);
            vertices.push_back(nextY);
            vertices.push_back(nextZ);
        }
    }

    vertexCount =  vertices.size();
    initBuffers(vertices);
}

void ToroideDavid::initBuffers(std::vector<float>& vertices) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vboVertices);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(0);
}

void ToroideDavid::render() {

    glBindVertexArray(vao);

    for (int i = 0; i < numMajorSegments; ++i) {
        glDrawArrays(GL_TRIANGLE_STRIP, i * (numMinorSegments + 1) * 2, (numMinorSegments + 1) * 2);
    }

    glBindVertexArray(0);
}

ToroideDavid::~ToroideDavid() {

}


