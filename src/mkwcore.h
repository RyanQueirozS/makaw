#ifndef MAKAW_CORE_H
#define MAKAW_CORE_H

#include "mkwtypes.h"

#include <stdint.h>
#include <stdbool.h>

#ifndef MAKAW_CORE_API
#define MAKAW_CORE_API
#endif // MAKAW_CORE_API

// Returns the window pointer
MAKAW_CORE_API void *mkwcore_init_windowing(int width, int height,
                                            const char *title, void *monitor,
                                            void *share);

MAKAW_CORE_API MakawStatus mkwcore_init_graphics_lib();

// Returns the shader
MAKAW_CORE_API uint32_t mkwcore_create_shader(enum MakawShaderType shader_type,
                                              const char *shader_code);

MAKAW_CORE_API uint32_t mkwcore_create_shader_program(
    uint32_t vertex_shader_id, uint32_t fragment_shader_id,
    uint32_t geometry_shader_id);

MAKAW_CORE_API uint32_t mkwcore_create_vertex_buffer(uint32_t size,
                                                     const void *data,
                                                     bool is_static);

MAKAW_CORE_API uint32_t mkwcore_create_index_buffer(uint32_t size,
                                                    const void *data,
                                                    bool is_static);

#endif // MAKAW_CORE_H
