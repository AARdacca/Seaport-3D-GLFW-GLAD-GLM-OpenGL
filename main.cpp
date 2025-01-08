#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "sphere.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawTriangle(unsigned int& triangleVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawShipHull(unsigned int& shipHullVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawLiquidSurface(unsigned int& liquidSurfaceVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawShipPlatform(unsigned int& shipPlatformVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);
void drawLandSurface(unsigned int& landSurfaceVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);
void drawShipTurret(unsigned int& shipTurretVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);
void drawBoardingHouseWalls(unsigned int& boardingHouseWallsVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);
void drawAllPurposeSticks(unsigned int& allPurposeSticksVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);
void drawFlatSurfaceLightHolder(unsigned int& flatSurfaceLightHolderVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);
void drawLorryTruckCockpit(unsigned int& lorryTruckCockpitVAO, Shader & lightingShader, glm::mat4 model, float r, float g, float b);







// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(0.5f, 0.0f, 6.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// direction of directional light
glm::vec3 directionalLight_direction = glm::vec3(-1.0f, 1.0f, -1.0f);

DirectionalLight directionalLight(-directionalLight_direction, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(1.50f,  1.50f,  0.0f),
    glm::vec3(1.5f,  -1.5f,  0.0f),
    glm::vec3(-1.5f,  1.5f,  0.0f),
    glm::vec3(-1.5f,  -1.5f,  0.0f),

    // Custom made Lights from here
    glm::vec3(2.0f,  1.5f,  -6.0f),
    glm::vec3(1.0f,  0.5f,  -5.4f),
    glm::vec3(2.0f,  1.0f,  3.0f),
};

PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);


// Custom made Lights from here

PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);

PointLight pointlight6(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);

PointLight pointlight7(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);


// light settings
bool directionalLightOn = false;
bool pointLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


// ---------------------------------------------------------------------------------------------------------------------------------------- Toggle
bool doorClose = false;
bool shipDepart = false;
bool clearSky = false;

int main()
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shipyard Explore!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // --------------------------------------------------------------------- Cube

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);



    // second, configure the light's VAO ------------------------------------ Light Cube
    unsigned int lightCubeVAO, lightVBO, lightEBO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightVBO);
    glGenBuffers(1, &lightEBO);

    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    
    //------------------------------------------------- 3D Triangle
    float triangle_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, -1.0f, 1.0f, 0.0f,

        0.5f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, -1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,

        1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    };

    unsigned int triangleVAO, triangleVBO;
    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(triangleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();
    //lightingShader.use();

    //----------------------------------------------------------------------------------------------------------- Ship Hull
    float shipHull_vertices[] = {
        // positions      // normals
        -1.0f, 0.2f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, 0.2f, 0.1f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.2f, 0.1f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.2f, -0.1f, 0.0f, -1.0f, 0.0f,
        -0.5f, 0.2f, -0.1f, 0.0f, -1.0f, 0.0f,

        -1.01f, 0.23f, 0.0f, -1.0f, -1.0f, 0.0f,
        -0.5f, -0.2f, 0.0f, -1.0f, -1.0f, 0.0f,
        -0.5f, 0.23f, 0.1f, -1.0f, -1.0f, 0.0f,

        -1.01f, 0.23f, 0.0f, -1.0f, -1.0f, 0.0f,
        -0.5f, -0.2f, 0.0f, -1.0f, -1.0f, 0.0f,
        -0.5f, 0.23f, -0.1f, -1.0f, -1.0f, 0.0f,

        1.0f, 0.23f, 0.1f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.23f, -0.1f, 1.0f, 0.0f, 0.0f,
        1.0f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.99f, 0.23f, 0.1f, 0.0f, 1.0f, 0.0f,
        -0.49f, 0.23f, 0.1f, 0.0f, 1.0f, 0.0f,
        -0.49f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.99f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.99f, 0.23f, -0.1f, 0.0f, 1.0f, 0.0f,
        -0.49f, 0.23f, -0.1f, 0.0f, 1.0f, 0.0f,
        -0.49f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.99f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,


    };

    unsigned int shipHullVAO, shipHullVBO;
    glGenVertexArrays(1, &shipHullVAO);
    glGenBuffers(1, &shipHullVBO);

    glBindVertexArray(shipHullVAO);

    glBindBuffer(GL_ARRAY_BUFFER, shipHullVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(shipHull_vertices), shipHull_vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------------------------------------------------  Liquid Surface
    float liquidSurface_Vertices[] = {
        80.0f,  0.0f,  -2.0f,  0.0f,  1.0f,  0.0f,
        -80.0f,  0.0f, -2.0f,  0.0f,  1.0f,  0.0f,  
        -80.0f,  0.0f,  80.0f,  0.0f,  1.0f,  0.0f,  
        80.0f,  0.0f,  80.0f,  0.0f,  1.0f,  0.0f,  

    };



    unsigned int liquidSurfaceVAO, liquidSurfaceVBO;
    glGenVertexArrays(1, &liquidSurfaceVAO);
    glGenBuffers(1, &liquidSurfaceVBO);

    glBindVertexArray(liquidSurfaceVAO);
    glBindBuffer(GL_ARRAY_BUFFER, liquidSurfaceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(liquidSurface_Vertices), liquidSurface_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // -------------------------------------------------------------  Ship Platform
    float shipPlatform_Vertices[] = {
        // positions      // normals
         2.0f, 0.1f, 1.0f,  0.0f,  0.0f,  1.0f,
         2.0f, -0.1f, 1.0f,  0.0f,  0.0f,  1.0f,
         -2.0f, -0.1f, 1.0f,  0.0f,  0.0f,  1.0f,
         -2.0f, 0.1f, 1.0f,  0.0f,  0.0f,  1.0f,

         2.0f, 0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,
         2.0f, -0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,
         -2.0f, -0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,
         -2.0f, 0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,

         -2.0f, 0.1f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -2.0f, 0.1f, -1.0f,  -1.0f,  0.0f,  0.0f,
         -2.0f, -0.1f, -1.0f,  -1.0f,  0.0f,  0.0f,
         -2.0f, -0.1f, 1.0f,  -1.0f,  0.0f,  0.0f,

         2.0f, 0.1f, 1.0f,  1.0f,  0.0f,  0.0f,
         2.0f, 0.1f, -1.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -0.1f, -1.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -0.1f, 1.0f,  1.0f,  0.0f,  0.0f,

         2.0f, -0.1f, 1.0f,  0.0f,  -1.0f,  0.0f,
         2.0f, -0.1f, -1.0f,  0.0f,  -1.0f,  0.0f,
         -2.0f, -0.1f, -1.0f,  0.0f,  -1.0f,  0.0f,
         -2.0f, -0.1f, 1.0f,  0.0f,  -1.0f,  0.0f,

         2.0f, 0.1f, 1.0f,  0.0f,  1.0f,  0.0f,
         2.0f, 0.1f, -1.0f,  0.0f,  1.0f,  0.0f,
         -2.0f, 0.1f, -1.0f,  0.0f,  1.0f,  0.0f,
         -2.0f, 0.1f, 1.0f,  0.0f,  1.0f,  0.0f,

    };



    unsigned int shipPlatformVAO, shipPlatformVBO;
    glGenVertexArrays(1, &shipPlatformVAO);
    glGenBuffers(1, &shipPlatformVBO);

    glBindVertexArray(shipPlatformVAO);
    glBindBuffer(GL_ARRAY_BUFFER, shipPlatformVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(shipPlatform_Vertices), shipPlatform_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // -------------------------------------------------------------  Land Surface
    float landSurface_Vertices[] = {
        80.0f,  0.0f,  -4.0f,  0.0f,  1.0f,  0.0f,
        -80.0f,  0.0f, -4.0f,  0.0f,  1.0f,  0.0f,
        -80.0f,  0.0f, -2.0f,  0.0f,  1.0f,  0.0f,
        80.0f,  0.0f,  -2.0f,  0.0f,  1.0f,  0.0f,
    };



    unsigned int landSurfaceVAO, landSurfaceVBO;
    glGenVertexArrays(1, &landSurfaceVAO);
    glGenBuffers(1, &landSurfaceVBO);

    glBindVertexArray(landSurfaceVAO);
    glBindBuffer(GL_ARRAY_BUFFER, landSurfaceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(landSurface_Vertices), landSurface_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // -------------------------------------------------------------  shipTurret
    float shipTurret_Vertices[] = {
        // positions      // normals
        1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,

        1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  -1.0f,
        1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  -1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  -1.0f,
        -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  -1.0f,

        -1.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -1.0f, 1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,

        1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,

        1.0f, -1.0f, 1.0f,  0.0f,  -1.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  0.0f,  -1.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f,  -1.0f,  0.0f,
        -1.0f, -1.0f, 1.0f,  0.0f,  -1.0f,  0.0f,

        1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        1.0f, 1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f, 1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
    };



    unsigned int shipTurretVAO, shipTurretVBO;
    glGenVertexArrays(1, &shipTurretVAO);
    glGenBuffers(1, &shipTurretVBO);

    glBindVertexArray(shipTurretVAO);
    glBindBuffer(GL_ARRAY_BUFFER, shipTurretVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(shipTurret_Vertices), shipTurret_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);



	// -------------------------------------------------------------  boardingHouseWalls
	float boardingHouseWalls_Vertices[] = {
        // positions      // normals
         2.0f, 0.05f, 1.0f,  0.0f,  0.0f,  1.0f,
         2.0f, -0.05f, 1.0f,  0.0f,  0.0f,  1.0f,
         -2.0f, -0.05f, 1.0f,  0.0f,  0.0f,  1.0f,
         -2.0f, 0.05f, 1.0f,  0.0f,  0.0f,  1.0f,

         2.0f, 0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,
         2.0f, -0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,
         -2.0f, -0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,
         -2.0f, 0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,

         -2.0f, 0.05f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -2.0f, 0.05f, -1.0f,  -1.0f,  0.0f,  0.0f,
         -2.0f, -0.05f, -1.0f,  -1.0f,  0.0f,  0.0f,
         -2.0f, -0.05f, 1.0f,  -1.0f,  0.0f,  0.0f,

         2.0f, 0.05f, 1.0f,  1.0f,  0.0f,  0.0f,
         2.0f, 0.05f, -1.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -0.05f, -1.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -0.05f, 1.0f,  1.0f,  0.0f,  0.0f,

         2.0f, -0.05f, 1.0f,  0.0f,  -1.0f,  0.0f,
         2.0f, -0.05f, -1.0f,  0.0f,  -1.0f,  0.0f,
         -2.0f, -0.05f, -1.0f,  0.0f,  -1.0f,  0.0f,
         -2.0f, -0.05f, 1.0f,  0.0f,  -1.0f,  0.0f,

         2.0f, 0.05f, 1.0f,  0.0f,  1.0f,  0.0f,
         2.0f, 0.05f, -1.0f,  0.0f,  1.0f,  0.0f,
         -2.0f, 0.05f, -1.0f,  0.0f,  1.0f,  0.0f,
         -2.0f, 0.05f, 1.0f,  0.0f,  1.0f,  0.0f,
	};

	unsigned int boardingHouseWallsVAO, boardingHouseWallsVBO;
	glGenVertexArrays(1, &boardingHouseWallsVAO);
	glGenBuffers(1, &boardingHouseWallsVBO);

	glBindVertexArray(boardingHouseWallsVAO);
	glBindBuffer(GL_ARRAY_BUFFER, boardingHouseWallsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boardingHouseWalls_Vertices), boardingHouseWalls_Vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);




    // -------------------------------------------------------------  allPurposeStick
    float allPurposeSticks_Vertices[] = {
        // positions      // normals
         0.05f, 0.05f, 1.0f,  0.0f,  0.0f,  1.0f,
         0.05f, -0.05f, 1.0f,  0.0f,  0.0f,  1.0f,
         -0.05f, -0.05f, 1.0f,  0.0f,  0.0f,  1.0f,
         -0.05f, 0.05f, 1.0f,  0.0f,  0.0f,  1.0f,

         0.05f, 0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,
         0.05f, -0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,
         -0.05f, -0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,
         -0.05f, 0.05f, -1.0f,  0.0f,  0.0f,  -1.0f,

         -0.05f, 0.05f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.05f, 0.05f, -1.0f,  -1.0f,  0.0f,  0.0f,
         -0.05f, -0.05f, -1.0f,  -1.0f,  0.0f,  0.0f,
         -0.05f, -0.05f, 1.0f,  -1.0f,  0.0f,  0.0f,

         0.05f, 0.05f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.05f, 0.05f, -1.0f,  1.0f,  0.0f,  0.0f,
         0.05f, -0.05f, -1.0f,  1.0f,  0.0f,  0.0f,
         0.05f, -0.05f, 1.0f,  1.0f,  0.0f,  0.0f,

         0.05f, -0.05f, 1.0f,  0.0f,  -1.0f,  0.0f,
         0.05f, -0.05f, -1.0f,  0.0f,  -1.0f,  0.0f,
         -0.05f, -0.05f, -1.0f,  0.0f,  -1.0f,  0.0f,
         -0.05f, -0.05f, 1.0f,  0.0f,  -1.0f,  0.0f,

         0.05f, 0.05f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.05f, 0.05f, -1.0f,  0.0f,  1.0f,  0.0f,
         -0.05f, 0.05f, -1.0f,  0.0f,  1.0f,  0.0f,
         -0.05f, 0.05f, 1.0f,  0.0f,  1.0f,  0.0f,
    };



    unsigned int allPurposeSticksVAO, allPurposeSticksVBO;
    glGenVertexArrays(1, &allPurposeSticksVAO);
    glGenBuffers(1, &allPurposeSticksVBO);

    glBindVertexArray(allPurposeSticksVAO);
    glBindBuffer(GL_ARRAY_BUFFER, allPurposeSticksVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(allPurposeSticks_Vertices), allPurposeSticks_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // -------------------------------------------------------------  FlatSurfaceLight
    float flatSurfaceLight_Vertices[] = {
        1.0f,  0.0f,  -1.0f,  0.0f,  -1.0f,  0.0f,
        -1.0f,  0.0f, -1.0f,  0.0f,  -1.0f,  0.0f,
        -1.0f,  0.0f, 1.0f,  0.0f,  -1.0f,  0.0f,
        1.0f,  0.0f,  1.0f,  0.0f,  -1.0f,  0.0f,
    };



    unsigned int flatSurfaceLightVAO, flatSurfaceLightVBO;
    glGenVertexArrays(1, &flatSurfaceLightVAO);
    glGenBuffers(1, &flatSurfaceLightVBO);

    glBindVertexArray(flatSurfaceLightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, flatSurfaceLightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(flatSurfaceLight_Vertices), flatSurfaceLight_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // -------------------------------------------------------------  flatSurfaceLightHolder
    float flatSurfaceLightHolder_Vertices[] = {
        1.0f, 0.1f, 1.0f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.1f, 1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -0.1f, 1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, 0.1f, 1.0f,  0.0f,  0.0f,  1.0f,

        1.0f, 0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,
        1.0f, -0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,
        -1.0f, -0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,
        -1.0f, 0.1f, -1.0f,  0.0f,  0.0f,  -1.0f,

        -1.0f, 0.1f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -1.0f, 0.1f, -1.0f,  -1.0f,  0.0f,  0.0f,
        -1.0f, -0.1f, -1.0f,  -1.0f,  0.0f,  0.0f,
        -1.0f, -0.1f, 1.0f,  -1.0f,  0.0f,  0.0f,

        1.0f, 0.1f, 1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, 0.1f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -0.1f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -0.1f, 1.0f,  1.0f,  0.0f,  0.0f,

        1.0f, -0.1f, 1.0f,  0.0f,  -1.0f,  0.0f,
        1.0f, -0.1f, -1.0f,  0.0f,  -1.0f,  0.0f,
        -1.0f, -0.1f, -1.0f,  0.0f,  -1.0f,  0.0f,
        -1.0f, -0.1f, 1.0f,  0.0f,  -1.0f,  0.0f,

        1.0f, 0.1f, 1.0f,  0.0f,  1.0f,  0.0f,
        1.0f, 0.1f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f, 0.1f, -1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f, 0.1f, 1.0f,  0.0f,  1.0f,  0.0f,
    };



    unsigned int flatSurfaceLightHolderVAO, flatSurfaceLightHolderVBO;
    glGenVertexArrays(1, &flatSurfaceLightHolderVAO);
    glGenBuffers(1, &flatSurfaceLightHolderVBO);

    glBindVertexArray(flatSurfaceLightHolderVAO);
    glBindBuffer(GL_ARRAY_BUFFER, flatSurfaceLightHolderVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(flatSurfaceLightHolder_Vertices), flatSurfaceLightHolder_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // -------------------------------------------------------------  lorryTruckCockpit
    float lorryTruckCockpit_Vertices[] = {
        0.1f, 0.1f, 0.1f,  0.0f,  0.0f,  1.0f,
        0.1f, -0.1f, 0.1f,  0.0f,  0.0f,  1.0f,
        -0.1f, -0.1f, 0.1f,  0.0f,  0.0f,  1.0f,
        -0.1f, 0.1f, 0.1f,  0.0f,  0.0f,  1.0f,

        0.1f, 0.1f, -0.1f,  0.0f,  0.0f,  -1.0f,
        0.1f, -0.1f, -0.1f,  0.0f,  0.0f,  -1.0f,
        -0.1f, -0.1f, -0.1f,  0.0f,  0.0f,  -1.0f,
        -0.1f, 0.1f, -0.1f,  0.0f,  0.0f,  -1.0f,

        -0.1f, 0.1f, 0.1f,  -1.0f,  0.0f,  0.0f,
        -0.1f, 0.1f, -0.1f,  -1.0f,  0.0f,  0.0f,
        -0.1f, -0.1f, -0.1f,  -1.0f,  0.0f,  0.0f,
        -0.1f, -0.1f, 0.1f,  -1.0f,  0.0f,  0.0f,

        0.1f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f,
        0.1f, 0.1f, -0.1f,  1.0f,  0.0f,  0.0f,
        0.1f, -0.1f, -0.1f,  1.0f,  0.0f,  0.0f,
        0.1f, -0.1f, 0.1f,  1.0f,  0.0f,  0.0f,

        0.1f, -0.1f, 0.1f,  0.0f,  -1.0f,  0.0f,
        0.1f, -0.1f, -0.1f,  0.0f,  -1.0f,  0.0f,
        -0.1f, -0.1f, -0.1f,  0.0f,  -1.0f,  0.0f,
        -0.1f, -0.1f, 0.1f,  0.0f,  -1.0f,  0.0f,

        0.1f, 0.1f, 0.1f,  0.0f,  1.0f,  0.0f,
        0.1f, 0.1f, -0.1f,  0.0f,  1.0f,  0.0f,
        -0.1f, 0.1f, -0.1f,  0.0f,  1.0f,  0.0f,
        -0.1f, 0.1f, 0.1f,  0.0f,  1.0f,  0.0f,
    };



    unsigned int lorryTruckCockpitVAO, lorryTruckCockpitVBO;
    glGenVertexArrays(1, &lorryTruckCockpitVAO);
    glGenBuffers(1, &lorryTruckCockpitVBO);

    glBindVertexArray(lorryTruckCockpitVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lorryTruckCockpitVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lorryTruckCockpit_Vertices), lorryTruckCockpit_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);




    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        if (clearSky) {
            glClearColor(0.1f, 0.9f, 0.9f, 1.0f);
        }
        else {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        pointlight1.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);

        directionalLight.setUpLight(lightingShader);

        // activate shader
        lightingShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);


        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));


        //Drawing a sphere
        Sphere sphere1 = Sphere();
                         //r    g     b      values
        sphere1.setColor(0.2f, 1.0f, 0.3f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.8f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        model = translateMatrix * scaleMatrix;
        sphere1.drawSphere(lightingShader, model);


        //Drawing a triangle
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -1.0f, -0.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        model = translateMatrix * scaleMatrix;
                                                         //r    g     b      values
        drawTriangle(triangleVAO, lightingShader, model, 0.8f, 0.3f, 1.0f);


        //Drawing a cube
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.8f, -0.4f, -0.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        model = translateMatrix * scaleMatrix;
                                                 //r    g     b      values
        drawCube(cubeVAO, lightingShader, model, 0.1f, 0.6f, 1.0f);

        
        //----------------------------------------------------------------------------------------------------------- Ship Hull Draw
        glm::vec3 time = glm::vec3(fmod(glfwGetTime() * 1.0f, 60.0f), 0.0f, 0.0f);

        if (time.x <= 30.0f) {
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + time.x, 0.0f, 5.0f)); // Loops after 10 units
        }
        else {
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(360.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + 60-time.x, 0.0f, 7.0f));
        }
        glm::mat4 temp01 = translateMatrix * rotateXMatrix * rotateZMatrix;
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateZMatrix;
        //r    g     b      valuesy
        drawShipHull(shipHullVAO, lightingShader, model, 0.2f, 0.0f, 0.0f);


        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 temp02;
        temp02 = model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;
        drawShipHull(shipHullVAO, lightingShader, model, 0.2f, 0.0f, 0.0f);

        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.0f, 0.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 temp03;
        temp03 = model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;
        drawShipHull(shipHullVAO, lightingShader, model, 0.6f, 0.6f, 0.6f);

        glm::mat4 temp04;
        if (shipDepart) {
            if (time.x <= 30.0f) {
                rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                rotateZMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, 0.9 + time.x)); // Loops after 10 units
            }
            else {
                rotateXMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                rotateZMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                translateMatrix = glm::translate(identityMatrix, glm::vec3(1.3f, 0.0f, 0.9 + 60 - time.x));
            }
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
            temp04 = model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;
            //r    g     b      valuesy
            drawShipHull(shipHullVAO, lightingShader, model, 0.6f, 0.6f, 0.6f);
        }

        //----------------------------------------------------------------------------------------------------------- Liquid Surface Draw
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -0.05f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;

        //r    g     b      values
        drawLiquidSurface(liquidSurfaceVAO, lightingShader, model, 0.0f, 0.0f, 0.9f);

        //----------------------------------------------------------------------------------------------------------- Ship Platform Draw
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;

        //r    g     b      values
        drawShipPlatform(shipPlatformVAO, lightingShader, model, 0.7f, 0.3f, 0.5f);

        //----------------------------------------------------------------------------------------------------------- Land Surface Draw Beach
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -0.05f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;

        //r    g     b      values
        drawLandSurface(landSurfaceVAO, lightingShader, model, 0.5f, 0.5f, 0.0f);

        //----------------------------------------------------------------------------------------------------------- Land Surface Draw Grass
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -0.05f, 16.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 10.0));
        model = translateMatrix * scaleMatrix;
        drawLandSurface(landSurfaceVAO, lightingShader, model, 0.0f, 0.5f, 0.5f);

        //----------------------------------------------------------------------------------------------------------- Land Surface Draw Road
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -0.04f, 15.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 1.0f, 9.5));
        model = translateMatrix * scaleMatrix;
        drawLandSurface(landSurfaceVAO, lightingShader, model, 0.4f, 0.4f, 0.4f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85f, -0.039f, 15.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.001f, 1.0f, 9.5));
        model = translateMatrix * scaleMatrix;
        drawLandSurface(landSurfaceVAO, lightingShader, model, 1.0f, 1.0f, 1.0f); // White Line Left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.15f, -0.039f, 15.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.001f, 1.0f, 9.5));
        model = translateMatrix * scaleMatrix;
        drawLandSurface(landSurfaceVAO, lightingShader, model, 1.0f, 1.0f, 1.0f); // White Line Right
        //----------------------------------------------------------------------------------------------------------- Land Surface Draw Road Parking
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.3f, -0.04f, 4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.06f, 1.0f, 3.5));
        model = translateMatrix * scaleMatrix;
        drawLandSurface(landSurfaceVAO, lightingShader, model, 0.4f, 0.4f, 0.4f);


        //----------------------------------------------------------------------------------------------------------- Ship Turret
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, 2.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.12f, 0.15f, 0.08f));
        model = temp01 * scaleMatrix * translateMatrix;
        //r    g     b      values
		drawShipTurret(shipTurretVAO, lightingShader, model, 0.6f, 0.0f, 0.1f);
        model = temp02 * scaleMatrix * translateMatrix;
        drawShipTurret(shipTurretVAO, lightingShader, model, 0.6f, 0.0f, 0.1f);
        model = temp03 * scaleMatrix * translateMatrix;
        drawShipTurret(shipTurretVAO, lightingShader, model, 0.0f, 0.0f, 0.9f);
        if (shipDepart) {
            model = temp04 * scaleMatrix * translateMatrix;
            drawShipTurret(shipTurretVAO, lightingShader, model, 0.0f, 0.9f, 0.9f);
        }

		//----------------------------------------------------------------------------------------------------------- Boarding House walls
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, 0.0f, -2.05f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.0f, 1.0f));
		model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix ;
		drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.9f, 0.9f, 0.9f); // Left Front
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.5f, 0.0f, -2.05f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.9f, 0.9f, 0.9f); // Right Front
        if (doorClose) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -2.05f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 1.0f));
            model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
            drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.3f, 0.3f, 0.3f); // Door Front
        }
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, 0.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.9f, 0.9f, 0.9f); // Left Back
        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5f, 0.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.9f, 0.9f, 0.9f); // Right Back
        if (doorClose) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.0f, -4.00f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 1.0f));
            model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
            drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.3f, 0.3f, 0.3f); // Door Back
        }
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 1.4f, -2.05f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.75f, 0.4f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.0f, 1.0f, 0.0f); // Up Front
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 1.4f, -4.00f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.75f, 0.4f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.0f, 1.0f, 0.0f); // Up Back
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 1.8f, -3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.75f, 1.0f, 1.3f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.0f, 1.0f, 0.0f); // Celling
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.0f, -3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.75f, 1.0f, 1.1f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 1.0f, 1.0f, 1.0f); // Floor
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5f, 0.85f, -3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 0.5f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateZMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.0f, 1.0f, 0.0f); // Left
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 0.85f, -3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 0.5f));
        model = translateMatrix * scaleMatrix * rotateXMatrix * rotateZMatrix;
        drawBoardingHouseWalls(boardingHouseWallsVAO, lightingShader, model, 0.0f, 1.0f, 0.0f); // Right


        //----------------------------------------------------------------------------------------------------------- All Purpose Sticks
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, 1.9f, -1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Upper Left Light Grabber
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, 1.8f, -0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Upper Left Light Grabber Hook
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.6f, 1.9f, -1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Upper Right Light Grabber
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.6f, 1.8f, -0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Upper Right Light Grabber Hook
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 1.55f, -5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.4f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Middle Right Behind Light Grabber
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.3f, 0.09f, -3.8f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.8f, 0.8f));
        model = translateMatrix * scaleMatrix * rotateYMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Container 1 -> X axis

        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.4f, 0.09f, -3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 0.8f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Container 2 -> Z axis

        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, 0.15f, 3.1f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix * rotateXMatrix;
        //r    g     b      values
        drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.396f, 0.263f, 0.129f); // Light Guide Stick Right

        //----------------------------------------------------------------------------------------------------------- Tree 1

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, 0.5f, -11.0f));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 1.0f));
        //model = translateMatrix * scaleMatrix * rotateXMatrix;
        ////r    g     b      values
        //drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.396f, 0.263f, 0.129f); // Tree Trunk
        //Sphere sphere2 = Sphere();
        ////r    g     b      values
        //sphere2.setColor(0.0f, 0.8f, 0.0f);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, 1.1f, -11.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        //model = translateMatrix * scaleMatrix;
        //sphere2.drawSphere(lightingShader, model); // Tree Leaf

        for (float x = -1.4f; x >= -8.0f; x -= 3.0f)
        {
            for (float z = -11.0f; z >= -18.0f; z -= 3.0f)
            {
                // -------------------------------------------------
                // 1) Draw the Tree Trunk
                // -------------------------------------------------
                glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0.5f, z));
                glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 1.0f));
                glm::mat4 model = translateMatrix * scaleMatrix * rotateXMatrix;
                drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.396f, 0.263f, 0.129f);
                // -------------------------------------------------
                // 2) Draw the Tree Leaf
                // -------------------------------------------------
                Sphere sphere2;
                sphere2.setColor(0.0f, 0.8f, 0.0f); // r, g, b
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 1.1f, z));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
                model = translateMatrix * scaleMatrix;
                sphere2.drawSphere(lightingShader, model);
            }
        }

        //----------------------------------------------------------------------------------------------------------- Tree 2

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(4.9f, 0.5f, -11.0f));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 1.0f));
        //model = translateMatrix * scaleMatrix * rotateXMatrix;
        ////r    g     b      values
        //drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.396f, 0.263f, 0.129f); // Tree Trunk
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(4.9f, 1.3f, -11.0f));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.4f, 0.4f));
        //model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
        ////r    g     b      values
        //drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.0f, 0.9f, 0.0f);
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = translateMatrix * scaleMatrix * rotateXMatrix * rotateZMatrix;
        ////r    g     b      values
        //drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.0f, 0.9f, 0.0f);


        for (float x = 4.9f; x <= 80.0f; x += 1.5f)
        {
            for (float z = -11.0f; z >= -18.0f; z -= 3.0f)
            {
                // -------------------------------------------------
                // 1) Draw the Tree Trunk
                // -------------------------------------------------
                glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0.5f, z));
                glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 1.0f));
                glm::mat4 model = translateMatrix * scaleMatrix * rotateXMatrix;
                drawAllPurposeSticks(allPurposeSticksVAO, lightingShader, model, 0.396f, 0.263f, 0.129f);
                // -------------------------------------------------
                // 2) Draw the First Flat Surface Light Holder
                // -------------------------------------------------
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 1.3f, z));
                rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                glm::mat4 rotateYMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.4f, 0.4f));
                model = translateMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix;
                drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.0f, 0.9f, 0.0f);
                // -------------------------------------------------
                // 3) Draw the Second Flat Surface Light Holder
                // -------------------------------------------------
                glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = translateMatrix * scaleMatrix * rotateXMatrix * rotateZMatrix;
                drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.0f, 0.9f, 0.0f);
            }
        }


        //----------------------------------------------------------------------------------------------------------- Flat Surface Light Holder
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 1.521f, -6.0f)); // pointLightPositions[4]
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.7f, 0.3f, 0.5f);

        //----------------------------------------------------------------------------------------------------------- Lorry Truck 1
        Sphere sphere3;
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.13f, -5.3f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        //model = translateMatrix * scaleMatrix;
        ////r    g     b      values
        //drawLorryTruckCockpit(lorryTruckCockpitVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Lorry Cockpit
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.02f, -5.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.4f));
        //model = translateMatrix * scaleMatrix;
        ////r    g     b      values
        //drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.7f, 0.3f, 0.5f); // Lorry Engine Frame
        //sphere3.setColor(0.4f, 0.4f, 0.4f); // r, g, b
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, 0.01f, -5.29f)); // Front Wheels Left
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.045f, 0.045f));
        //model = translateMatrix * scaleMatrix;
        //sphere3.drawSphere(lightingShader, model);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.01f, -5.29f)); // Front Wheels Left
        //model = translateMatrix * scaleMatrix;
        //sphere3.drawSphere(lightingShader, model);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, 0.01f, -4.7f)); // Rear Wheels 2 Right
        //model = translateMatrix * scaleMatrix;
        //sphere3.drawSphere(lightingShader, model);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.01f, -4.7f)); // Rear Wheels 2 Left
        //model = translateMatrix * scaleMatrix;
        //sphere3.drawSphere(lightingShader, model);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, 0.01f, -4.8f)); // Rear Wheels 1 Right
        //model = translateMatrix * scaleMatrix;
        //sphere3.drawSphere(lightingShader, model);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.01f, -4.8f)); // Rear Wheels 1 Left
        //model = translateMatrix * scaleMatrix;
        //sphere3.drawSphere(lightingShader, model);

        //----------------------------------------------------------------------------------------------------------- Lorry Truck 1

        float zPos = -5.3f;
        if (time.x <= 30.0f)
        {
            float fraction = time.x / 30.0f;
            zPos = -5.3f - fraction * (35.0f - 5.3f);
        }
        else
        {
            float fraction = (time.x - 30.0f) / 30.0f;
            zPos = -35.0f + fraction * (35.0f - 5.3f);
        }
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.13f, zPos));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));  //for sphere size
        model = translateMatrix * scaleMatrix;
        drawLorryTruckCockpit(lorryTruckCockpitVAO, lightingShader, model, 0.0f, 0.5f, 0.5f);  // Lorry Cockpit
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.02f, zPos + 0.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.4f));
        model = translateMatrix * scaleMatrix;
        drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.7f, 0.3f, 0.5f); // Lorry Engine Frame
        sphere3.setColor(0.4f, 0.4f, 0.4f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, 0.01f, zPos + 0.01f)); // Front Wheels Left
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.045f, 0.045f));
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.01f, zPos + 0.01f)); // Front Wheels Left
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, 0.01f, zPos + 0.6f)); // Rear Wheels 2 Right
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.01f, zPos + 0.6f)); // Rear Wheels 2 Left
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, 0.01f, zPos + 0.5f)); // Rear Wheels 1 Right
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.01f, zPos + 0.5f)); // Rear Wheels 1 Left
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);

        //----------------------------------------------------------------------------------------------------------- Lorry Truck 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.13f, -5.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawLorryTruckCockpit(lorryTruckCockpitVAO, lightingShader, model, 0.0f, 0.5f, 0.5f); // Lorry Cockpit
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.02f, -5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.4f));
        model = translateMatrix * scaleMatrix;
        //r    g     b      values
        drawFlatSurfaceLightHolder(flatSurfaceLightHolderVAO, lightingShader, model, 0.7f, 0.3f, 0.5f); // Lorry Engine Frame
        sphere3.setColor(0.4f, 0.4f, 0.4f); // r, g, b
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.01f, -5.29f)); // Front Wheels Left
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.045f, 0.045f));
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.01f, -5.29f)); // Front Wheels Left
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.01f, -4.7f)); // Rear Wheels 2 Right
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.01f, -4.7f)); // Rear Wheels 2 Left
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.01f, -4.8f)); // Rear Wheels 1 Right
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.01f, -4.8f)); // Rear Wheels 1 Left
        model = translateMatrix * scaleMatrix;
        sphere3.drawSphere(lightingShader, model);

        // Also draw the lamp object(s)
        // The white cubes are lamp objects
        // As we can't see the point where the point lights are, we are representing the points with the white cubes
        // We don't need the lighting effects on the cubes, that's why we are using simple shader, with only one color element
        // fragmentShader.fs and vertexShader.fs are the simple shaders codes. 
        // SEE THESE TWO FILES!
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            if(pointLightOn)
                ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            else
                ourShader.setVec3("color", glm::vec3(0.25f, 0.25f, 0.25f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // Custom made Lights are from here...


        //----------------------------------------------------------------------------------------------------------- Flat Surface Light
        glBindVertexArray(flatSurfaceLightVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[4]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        if (pointLightOn)
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
        else
            ourShader.setVec3("color", glm::vec3(0.25f, 0.25f, 0.25f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
        glBindVertexArray(0);

        //----------------------------------------------------------------------------------------------------------- Flat Surface Light Lorry
        glBindVertexArray(flatSurfaceLightVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[5]);
        //model = glm::translate(model, glm::vec3(0.0f, -0.45f, -0.001f));
        model = glm::translate(model, glm::vec3(0.0f, -0.45f, 5.299f + zPos));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.02f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        if (pointLightOn)
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
        else
            ourShader.setVec3("color", glm::vec3(0.25f, 0.25f, 0.25f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);

        //----------------------------------------------------------------------------------------------------------- Light Stick Guide
        glBindVertexArray(lightCubeVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[6]);
        model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        if (pointLightOn)
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
        else
            ourShader.setVec3("color", glm::vec3(0.25f, 0.25f, 0.25f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //----------------------------------------------------------------------------------------------------------- Custom Lights ends here


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawTriangle(unsigned int& triangleVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(triangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 24);
}

void drawShipHull(unsigned int& shipHullVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(shipHullVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
    glDrawArrays(GL_TRIANGLE_FAN, 5, 3);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 3);
    glDrawArrays(GL_TRIANGLE_FAN, 11, 3);
    glDrawArrays(GL_TRIANGLE_FAN, 14, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 18, 4);
    glBindVertexArray(0);
}


void drawLiquidSurface(unsigned int& liquidSurfaceVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(liquidSurfaceVAO);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 

    glBindVertexArray(0);

}

void drawShipPlatform(unsigned int& shipPlatformVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(shipPlatformVAO);

    for (int i = 0; i < 6; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4); // Each face has 4 vertices
    }
    glBindVertexArray(0);

}


void drawLandSurface(unsigned int& landSurfaceVAO, Shader & lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(landSurfaceVAO);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Each face has 4 vertices
    glBindVertexArray(0);

}




void drawShipTurret(unsigned int& shipTurretVAO, Shader & lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(shipTurretVAO);

    for (int i = 0; i < 6; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4); // Each face has 4 vertices (1 center + 5 corners)
    }
    glBindVertexArray(0);

}



void drawBoardingHouseWalls(unsigned int& boardingHouseWallsVAO, Shader & lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
	lightingShader.use();

	lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
	lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
	lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	lightingShader.setFloat("material.shininess", 32.0f);

	lightingShader.setMat4("model", model);

	glBindVertexArray(boardingHouseWallsVAO);
	for (int i = 0; i < 6; ++i) {
		glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
	}
	glBindVertexArray(0);

}


void drawAllPurposeSticks(unsigned int& allPurposeSticksVAO, Shader & lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(allPurposeSticksVAO);
    for (int i = 0; i < 6; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    glBindVertexArray(0);

}

void drawFlatSurfaceLightHolder(unsigned int& flatSurfaceLightHolderVAO, Shader & lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(flatSurfaceLightHolderVAO);
    for (int i = 0; i < 6; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    glBindVertexArray(0);

}





void drawLorryTruckCockpit(unsigned int& lorryTruckCockpitVAO, Shader & lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(lorryTruckCockpitVAO);

    glBindVertexArray(lorryTruckCockpitVAO);
    for (int i = 0; i < 6; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4); // Each face has 6 vertices (1 center + 5 corners)
    }
    glBindVertexArray(0);

}





// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }

    //--------------------------------------------------------------------------------------- Custom Toggle

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        doorClose = !doorClose;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        shipDepart = !shipDepart;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        clearSky = !clearSky;
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        if (directionalLightOn)
        {
            directionalLight.turnOff();
            directionalLightOn = !directionalLightOn;
        }
        else
        {
            directionalLight.turnOn();
            directionalLightOn = !directionalLightOn;
        }
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight3.turnOn();
            pointlight4.turnOn();
            pointLightOn = !pointLightOn;
        }
    }


    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();

            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
