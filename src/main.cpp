// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "main.h"






bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}






static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    style.FrameRounding = 12;
    ImGui::StyleColorsLight();
    style.Colors[ImGuiCol_Header] = RGBAtoIV4(36, 54, 74, 79);
 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.IniFilename = nullptr;
    ImFontConfig Font_cfg;
    Font_cfg.FontDataOwnedByAtlas = false;


    ImFont* Font = io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 18.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* Font_Big = io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 24.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    ImGui::StyleColorsLight();
    style.Colors[ImGuiCol_Header] = RGBAtoIV4(36, 54, 74, 79);
    int my_image_width = 100;
    int my_image_height = 100;
    GLuint my_image_texture = 0;
    bool ret = LoadTextureFromFile("jcly.png", &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);

    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        
        glfwPollEvents();

   
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        




        static bool show_demo_window = false;
        static bool show_another_window = false;
        static bool show_line = false;
        static bool show_Circle = false;
        static bool show_box = false;


        static float line_cx = 2;
        static float Circle_cx = 2;
        static float box_cx = 2;


        static float box_yj = 20;

        static ImVec2 line_coord1{ 200,200 };
        static ImVec2 line_coord2{ 200,400 };
        static ImVec2 box_coord1{ 200,300 };
        static ImVec2 box_coord2{ 350,550 };
        static ImVec2 Circle_coord{ 400,800 };


        static ImColor Circle_color = ImColor(255, 0, 0);
        static ImVec4  clear_color = ImVec4(0, 0, 0, 0);
        static ImColor line_color = ImColor(255, 0, 0);
        static ImColor box_color = ImColor(43, 255, 0);
        static ImGuiStyle ref_saved_style;
        static int style_idx = 0;
        


        if (show_Circle)
        {
            ImGui::GetForegroundDrawList()->AddCircle(Circle_coord, 100, Circle_color, 0, Circle_cx);
        }
        if (show_line)
        {
            ImGui::GetForegroundDrawList()->AddLine(line_coord1, line_coord2, line_color, line_cx);
        }
        if (show_box)
        {
            ImGui::GetForegroundDrawList()->AddRect(box_coord1, box_coord2, box_color, box_yj, NULL, box_cx);
        }
        if (show_demo_window)
        {
            ImGui::ShowDemoWindow();
        }
        {

            ImGui::Begin("test");
            ImGuiWindow* TheWindow = ImGui::GetCurrentWindow();
            ImVec2 leftuppos = TheWindow->Pos;
            ImVec2 size = ImGui::GetWindowSize();
            ImVec2 rightdownpos;
            rightdownpos.x = leftuppos.x + size.x;
            rightdownpos.y = leftuppos.y + size.y;
            TheWindow->DrawList->AddImage((void*)my_image_texture,leftuppos,rightdownpos);
            ImGui::Button("test");
            //ImGui::Image((void*)my_image_texture, ImVec2(my_image_width, my_image_height));
            ImGui::End();
        }

   

        {
          ImGui::Begin(u8"by,沐辰");
            ImGui::SetWindowSize({ 600, 600 }, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("功能"))
            {
                ImGui::Checkbox("简易计算器", &show_another_window);
                ImGui::Checkbox("展示demo", &show_demo_window);
                ImGui::Checkbox("绘制圆形", &show_Circle);
                ImGui::Checkbox("绘制射线", &show_line);
                ImGui::Checkbox("绘制矩形", &show_box);

            }
            if (ImGui::CollapsingHeader("设置"))
            {


                if (ImGui::TreeNode("绘制项目"))
                {
                    if (ImGui::TreeNode("圆角"))
                    {
                        ImGui::SliderFloat("矩形圆角", &box_yj, 1.0f, 100.0f);
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("宽度"))
                    {
                        ImGui::SliderFloat("圆形粗细", &Circle_cx, 1.0f, 10.0f);
                        ImGui::SliderFloat("射线粗细", &line_cx, 1.0f, 10.0f);
                        ImGui::SliderFloat("矩形粗细", &box_cx, 1.0f, 10.0f);
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("颜色"))
                    {
                        ImGui::ColorEdit3("射线颜色", (float*)&line_color);
                        ImGui::ColorEdit3("圆形颜色", (float*)&Circle_color);
                        ImGui::ColorEdit3("矩形颜色", (float*)&box_color);
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("位置"))
                    {
                        if (ImGui::TreeNode("射线位置"))
                        {
                            ImGui::SliderFloat("射线x1", &line_coord1.x, 1.0f, 1000.0f);
                            ImGui::SliderFloat("射线y1", &line_coord1.y, 1.0f, 1000.0f);
                            ImGui::SliderFloat("射线x2", &line_coord2.x, 1.0f, 1000.0f);
                            ImGui::SliderFloat("射线y2", &line_coord2.y, 1.0f, 1000.0f);
                            ImGui::TreePop();
                        }
                        if (ImGui::TreeNode("矩形位置"))
                        {
                            ImGui::SliderFloat("矩形1x", &box_coord1.x, 1.0f, 1000.0f);
                            ImGui::SliderFloat("矩形1y", &box_coord1.y, 1.0f, 1000.0f);
                            ImGui::SliderFloat("矩形2x", &box_coord2.x, 1.0f, 1000.0f);
                            ImGui::SliderFloat("矩形2y", &box_coord2.y, 1.0f, 1000.0f);
                            ImGui::TreePop();
                        }
                        if (ImGui::TreeNode("圆形位置"))
                        {
                            ImGui::SliderFloat("圆形x1", &Circle_coord.x, 1.0f, 1000.0f);
                            ImGui::SliderFloat("圆形y1", &Circle_coord.y, 1.0f, 1000.0f);
                            ImGui::TreePop();
                        }
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }



                if (ImGui::TreeNode("风格"))
                {
                    if (ImGui::Combo("颜色", &style_idx, "白色\0蓝色\0紫色\0"))
                    {
                        switch (style_idx)
                        {
                        case 0:
                            ImGui::StyleColorsLight();
                            style.Colors[ImGuiCol_Header] = RGBAtoIV4(36, 54, 74, 79);
                            break;
                        case 1:
                            ImGui::StyleColorsDark();
                            break;
                        case 2:
                            ImGui::StyleColorsClassic();
                            break;
                        }
                    }
                    ImGui::ColorEdit3("字体颜色", (float*)&style.Colors[0]);


                    ImGui::TreePop();
                }

            }
            ImGui::Text("fps ： (%.3f FPS)", io.Framerate);
            if (ImGui::Button("退出"))
            {
                exit(0);
            }
            ImGui::End();
        }
            if (show_another_window)
        {
            static int arr[2] = { 0,0 };
            static float arr1[2] = { 0,0 };
            ImGui::Begin("简易计算器");
            ImGui::SetWindowSize({ 600, 600 }, ImGuiCond_Once);

            if (ImGui::CollapsingHeader("加法"))
            {
                ImGui::SliderInt("被加数", &arr[0], 0, 10, "%d");
                ImGui::SliderInt("加数", &arr[1], 0, 10, "%d");
                ImGui::Text("结果=%d", arr[0] + arr[1]);
            }


            if (ImGui::CollapsingHeader("减法"))
            {
                ImGui::SliderInt("被减数", &arr[0], 0, 10, "%d");
                ImGui::SliderInt("减数", &arr[1], 0, 10, "%d");
                ImGui::Text("结果=%d", arr[0] - arr[1]);
            }


            if (ImGui::CollapsingHeader("乘法"))
            {
                ImGui::SliderInt("乘数1", &arr[0], 0, 10, "%d");
                ImGui::SliderInt("乘数2", &arr[1], 0, 10, "%d");
                ImGui::Text("结果=%d", arr[0] * arr[1]);
            }

            if (ImGui::CollapsingHeader("除法"))
            {
                ImGui::SliderFloat("被除数", &arr1[0], 0.0f, 10.0f, "%.0f");
                ImGui::SliderFloat("除数", &arr1[1], 0.0f, 10.0f, "%.0f");
                ImGui::Text("结果=%.3f", arr1[0] / arr1[1]);
            }

            if (ImGui::Button("关闭这个窗口"))
            {
                show_another_window = false;
            }
            ImGui::End();

        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
