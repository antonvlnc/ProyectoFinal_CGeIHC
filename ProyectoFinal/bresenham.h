#pragma once

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

GLuint VAO = 0;
GLuint VBO = 0;

void drawCircle(int radius, int centerX, int centerY, int width, int height) {
    // Validación de que el radio sea un número mayor que cero
    if (radius <= 0) {
        std::cerr << "Error: El radio debe ser un número mayor que cero." << std::endl;
        return;
    }

    std::vector<GLfloat> vertices;
    vertices.reserve(360 * 3); // Reservar espacio para los vértices, se multiplica por el número de coordenadas

    // Algoritmo de Bresenham para generar los vértices de la circunferencia
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    while (x <= y) {
        vertices.push_back(centerX + x);
        vertices.push_back(centerY + y);
        vertices.push_back(0.0f);
        vertices.push_back(centerX - x);
        vertices.push_back(centerY + y);
        vertices.push_back(0.0f);
        vertices.push_back(centerX + x);
        vertices.push_back(centerY - y);
        vertices.push_back(0.0f);
        vertices.push_back(centerX - x);
        vertices.push_back(centerY - y);
        vertices.push_back(0.0f);
        vertices.push_back(centerX + y);
        vertices.push_back(centerY + x);
        vertices.push_back(0.0f);
        vertices.push_back(centerX - y);
        vertices.push_back(centerY + x);
        vertices.push_back(0.0f);
        vertices.push_back(centerX + y);
        vertices.push_back(centerY - x);
        vertices.push_back(0.0f);
        vertices.push_back(centerX - y);
        vertices.push_back(centerY - x);
        vertices.push_back(0.0f);

        if (d < 0) {
            d += 4 * x + 6;
        }
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    // Escalar y normalizar los vértices de la circunferencia
    for (size_t i = 0; i < vertices.size(); i += 2) {
        vertices[i] = (vertices[i] - width / 2.0f) / (width / 2.0f);
        vertices[i + 1] = (vertices[i + 1] - height / 2.0f) / (height / 2.0f);
    }


    // Crear el búfer de vértices
    //GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);


    //geometria
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Dibujar la circunferencia
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, vertices.size() / 2);
    glBindVertexArray(0);

    // Limpiar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}