#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> 
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Font.h"
#pragma execution_character_set("utf-8")
ImVec4 RGBAtoIV4(int r, int g, int b, int a) {
    float newr = r / 255.0f;
    float newg = g / 255.0f;
    float newb = b / 255.0f;
    float newa = a / 255.0f;
    return ImVec4(newr, newg, newb, newa);
}
