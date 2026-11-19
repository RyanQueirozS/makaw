#include "makaw.h"

#include "mkwcore.h"
#include "mkwtypes.h"
#include "mkwmath.h"

#include <stdint.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

GLFWwindow *window;

unsigned int vbo;
unsigned int ibo;
unsigned int vao;

unsigned int vertex_shader;
unsigned int fragment_shader;
unsigned int shader_program;

uint64_t ibo_capacity = 1024, vbo_capacity = 1024 / 6;
uint64_t ibo_current_count = 0, vbo_current_count = 0;

const char *const V_SHADER_SOURCE =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char *const F_SHADER_SOURCE =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

// Internal
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Header impl
MakawStatus makaw_init() {
        window = mkwcore_init_windowing(800, 600, "makaw example", NULL, NULL);
        if (window == NULL) {
                printf("Failed to create GLFW window");
                glfwTerminate();
                return MAKAW_FAILURE;
        }
        glfwMakeContextCurrent(window);

        if (!mkwcore_init_graphics_lib()) {
                return MAKAW_FAILURE;
        }

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        vertex_shader =
            mkwcore_create_shader(MAKAW_SHADER_VERTEX, V_SHADER_SOURCE);

        fragment_shader =
            mkwcore_create_shader(MAKAW_SHADER_FRAGMENT, F_SHADER_SOURCE);

        shader_program =
            mkwcore_create_shader_program(vertex_shader, fragment_shader, 0);
        glLinkProgram(shader_program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glUseProgram(shader_program);

        // Setting up buffers
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        vbo = mkwcore_create_vertex_buffer(vbo_capacity, NULL, false);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void *)0);
        ibo = mkwcore_create_index_buffer(ibo_capacity, NULL, true);
        glEnableVertexAttribArray(0);

        return MAKAW_SUCCESS;
}

void makaw_exit() {
        glfwTerminate();
}

MakawStatus makaw_is_running() {
        return !glfwWindowShouldClose(window);
}

void makaw_clear() {
        ibo_current_count = 0;
        vbo_current_count = 0;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
}

void makaw_draw_triangle(MakawVec2 vertex_a, MakawVec2 vertex_b,
                         MakawVec2 vertex_c) {
        MakawVec3 vertices[3] = {
            MAKAW_VEC3_TO_VEC2(vertex_a, 0),
            MAKAW_VEC3_TO_VEC2(vertex_b, 0),
            MAKAW_VEC3_TO_VEC2(vertex_c, 0),
        };

        uint32_t indices[3] = {
            0 + vbo_current_count,
            1 + vbo_current_count,
            2 + vbo_current_count,
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, vbo_current_count * sizeof(MakawVec3),
                        sizeof(vertices), &vertices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                        ibo_current_count * sizeof(uint32_t), sizeof(indices),
                        &indices);
        vbo_current_count += sizeof(vertices) / sizeof(vertices[0]);
        ibo_current_count += sizeof(indices) / sizeof(indices[0]);
}

void makaw_draw_square(MakawSquare square) {
        float leftmost_x_value = square.position_center.x - square.width_x / 2,
              topmost_y_value = square.position_center.y - square.height_y / 2;

        MakawVec3 top_left = {leftmost_x_value, topmost_y_value,
                              square.depth_z};
        MakawVec3 top_right =
            mkwmath_vec3_add(top_left, (MakawVec3){square.width_x, 0, 0});

        MakawVec3 bottom_left =
            mkwmath_vec3_add(top_left, (MakawVec3){0, square.height_y, 0});
        MakawVec3 bottom_right =
            mkwmath_vec3_add(bottom_left, (MakawVec3){square.width_x, 0, 0});

        MakawVec3 vertices[4] = {
            top_left,
            top_right,
            bottom_left,
            bottom_right,
        };

        uint32_t indices[6] = {
            0 + vbo_current_count, 1 + vbo_current_count,
            2 + vbo_current_count, // First triangle
            1 + vbo_current_count, 2 + vbo_current_count,
            3 + vbo_current_count // Second triangle
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, vbo_current_count * sizeof(MakawVec3),
                        sizeof(vertices), &vertices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                        ibo_current_count * sizeof(uint32_t), sizeof(indices),
                        &indices);
        vbo_current_count += sizeof(vertices) / sizeof(vertices[0]);
        ibo_current_count += sizeof(indices) / sizeof(indices[0]);
}

void makaw_present() {
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, ibo_current_count, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
}

// Internal
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
}
