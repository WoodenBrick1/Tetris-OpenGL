#include "config.h"

std::filesystem::path sourceDir = std::filesystem::absolute(__FILE__).parent_path();

int main()
{

    GLFWwindow *window;

    if (!glfwInit())
    {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // clang-format off
    float vertices[] = {
        // Positions      // Colors
         0.05f,  0.05f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.05f, -0.05f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.05f, 0.0f, 0.0f, 0.0f, 0.0f,


};
    // clang-format on

    // Setup VAO and VBO
    unsigned int VAO,
        VBO;
    glGenVertexArrays(1, &VAO);

    // VAO and VBO for triangle
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int strideSize = 6;
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Setting Up Shader (after GLAD initialization)
    std::string vertexPath = (sourceDir / "shaders/vertex.txt").string();
    std::string fragmentPath = (sourceDir / "shaders/fragment.txt").string();

    std::cout << "Source directory: " << sourceDir << std::endl;
    std::cout << "Vertex shader path: " << vertexPath << std::endl;
    std::cout << "Fragment shader path: " << fragmentPath << std::endl;

    Shader shader(vertexPath.c_str(), fragmentPath.c_str());

    glClearColor(1.0f, 0.8f, 0.75f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
