#include "mkwcore.h"
#include "mkwtypes.h"

#include <stdint.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

// Internal

void log_opengl_shader(uint32_t shader_id);

// Header implementation
void *mkwcore_init_windowing(int width, int height, const char *title,
                             void *monitor, void *share) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        return glfwCreateWindow(width, height, title, monitor, share);
}

MakawStatus mkwcore_init_graphics_lib() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                printf("Failed to initialize GLAD");
                return MAKAW_FAILURE;
        }
        return MAKAW_SUCCESS;
}

uint32_t mkwcore_create_shader(enum MakawShaderType shader_type,
                               const char *shader_code) {
        uint32_t shader = 0;
        switch (shader_type) {
        case MAKAW_SHADER_VERTEX:
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
        case MAKAW_SHADER_FRAGMENT:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
        }
        glShaderSource(shader, 1, &shader_code, NULL);
        glCompileShader(shader);

        log_opengl_shader(shader);

        return shader;
}

uint32_t mkwcore_create_shader_program(uint32_t vertex_shader_id,
                                       uint32_t fragment_shader_id,
                                       uint32_t geometry_shader_id) {
        uint32_t shader_program = glCreateProgram();

        if (vertex_shader_id) {
                glAttachShader(shader_program, vertex_shader_id);
        }
        if (fragment_shader_id) {
                glAttachShader(shader_program, fragment_shader_id);
        }
        if (geometry_shader_id) {
                glAttachShader(shader_program, geometry_shader_id);
        }

        return shader_program;
}

uint32_t mkwcore_create_vertex_buffer(uint32_t size, const void *data,
                                      bool is_static) {
        uint32_t vbo = 0;
        uint32_t static_flag = is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size, data, static_flag);

        return vbo;
}

uint32_t mkwcore_create_index_buffer(uint32_t size, const void *data,
                                     bool is_static) {
        uint32_t vbo = 0;
        uint32_t static_flag = is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, static_flag);

        return vbo;
}

// Internal

void log_opengl_shader(uint32_t shader_id) {
        int success;
        char info_log[512];
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(shader_id, 512, NULL, info_log);
                printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED:%s\n",
                       info_log);
        }
}
