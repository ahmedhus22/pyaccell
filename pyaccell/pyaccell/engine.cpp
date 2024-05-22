#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <pyaccell/engine.hpp>
#include <pyaccell/shader.hpp>
#include <pyaccell/rules.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int FRAME_WIDTH = 300;
const unsigned int FRAME_HEIGHT = 200;

int pyaccell::run()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pyaccell", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    pyaccell::Shader screenShader(SHADER_PATH "framebuffers_screen.vs", SHADER_PATH "framebuffers_screen.fs");
    pyaccell::Shader simShader(SHADER_PATH "sim.vs", SHADER_PATH "sim.fs");

    // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    float quadVertices[] = { 
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    // screen quad VAO
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
    // shader configuration
    screenShader.use();
    screenShader.setInt("screenTexture", 0);

    // framebuffer configuration
    // -------------------------
    /**
        framebuffer(textureInput) -> textureOutput
        framebuffer_alt(textureOutput) -> textureInput
        swap or alternate framebuffers each loop
    */
    unsigned int framebuffer[2];
    unsigned int textureInput[2];
    unsigned int textureColorbuffer = pyaccell::create_color_texture(FRAME_WIDTH, FRAME_HEIGHT);
    glGenTextures(2, textureInput);
    glGenFramebuffers(2, framebuffer);
    for (int i=0; i<2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[i]);
        if (i == 0) {
            textureInput[i] = pyaccell::random_input_state(FRAME_WIDTH, FRAME_HEIGHT, 2);
        }
        else {
            textureInput[i] = pyaccell::create_empty_texture(FRAME_WIDTH, FRAME_HEIGHT);
        }
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
        glBindTexture(GL_TEXTURE_2D, textureInput[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, textureInput[i], 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // simShader uniforms
    // ------------------
    // set Binomial sampler to Texture Unit 1
    simShader.use();
    unsigned int textureBinomials = pyaccell::generate_binomials();
    simShader.setInt("uBinomial", 1);
    // set inputStates sampler to 2
    simShader.setInt("inputStates", 2);
    // set rule sampler (transition function) to 3 
    unsigned int rule[] = { // (temporary value for now)
        0,0,0,1,0,0,0,0,0,
        0,0,1,1,0,0,0,0,0
    };
    unsigned int textureRule = pyaccell::generate_rule(rule, 9, 2);
    simShader.setInt("rule", 3);
    simShader.setInt("numStates", 2);
    simShader.setInt("subIndices", 9);
    simShader.setInt("inputWidth", FRAME_WIDTH);
    simShader.setInt("inputHeight", FRAME_HEIGHT);

    screenShader.use();
    screenShader.setInt("screenTexture", 0);

    int input_index = 0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        int output_index = (input_index == 0) ? 1 : 0;

        // render
        // ------
        /*bind to framebuffer alternatively and "draw" to textureInput
            start with frame_index=0 as input and frame_index=1(alt_index) as output
        */
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[output_index]);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        simShader.use();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureBinomials);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textureRule);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureInput[input_index]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        input_index = output_index;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}