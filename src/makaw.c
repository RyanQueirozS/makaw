#include "makaw.h"

#include "mkwcore.h"
#include "mkwtypes.h"

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

uint32_t square_indices[6] = {
    0, 1, 2, // First triangle
    1, 2, 3  // Second triangle
};

const float VERTICES[3][3] = {{-0.5, -0.5, 0}, {0.5, -0.5, 0}, {0, 0.5, 0}};

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
        vbo = mkwcore_create_vertex_buffer(1024, NULL, false);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void *)0);
        ibo = mkwcore_create_index_buffer(100, square_indices, true);
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
}

void makaw_draw_triangle(MakawVec2 vertex_a, MakawVec2 vertex_b,
                         MakawVec2 vertex_c) {
        float vertices[3][3] = {
            {vertex_a.x, vertex_a.y, 0},
            {vertex_b.x, vertex_b.y, 0},
            {vertex_c.x, vertex_c.y, 0},
        };
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
}

void makaw_draw_square(MakawVec2 position_top_left, float height_bottom,
                       float lenght_right) {
        // TODO rewrite
        MakawVec3 top_left = {position_top_left.x, position_top_left.y, 0};
        MakawVec3 top_right = {position_top_left.x + lenght_right,
                               position_top_left.y, 0};
        MakawVec3 bottom_left = {position_top_left.x,
                                 position_top_left.y - height_bottom, 0};
        MakawVec3 bottom_right = {position_top_left.x + lenght_right,
                                  position_top_left.y - height_bottom, 0};
        MakawVec3 vertices[4] = {
            top_left,
            top_right,
            bottom_left,
            bottom_right,
        };
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
}

void makaw_draw_quad(MakawVec2 vertex_a, MakawVec2 vertex_b, MakawVec2 vertex_c,
                     MakawVec2 vertex_d) {
}

void makaw_present() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
}

// Internal
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
}
