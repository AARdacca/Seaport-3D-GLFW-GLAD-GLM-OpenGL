void 1111111111111drawTriangleFanCube(unsigned int& 1111111111111111triangleFanCubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);

















// -------------------------------------------------------------  Vertices for a cube using GL_TRIANGLE_FAN for each face
    float 111111triangleFanCube_Vertices[] = {
        // Front face (z = 0.5)
        0.0f,  0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  // Center vertex
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Bottom-left
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Bottom-right
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Top-right
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Top-left
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Close the fan

       // Back face (z = -0.5)
       0.0f,  0.0f, -0.5f,  0.0f,  0.0f, -1.0f,  // Center vertex
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Bottom-left
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Top-left
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Top-right
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Bottom-right
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // Close the fan

      // Left face (x = -0.5)
     -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,  // Center vertex
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  // Front-bottom
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  // Front-top
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  // Back-top
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  // Back-bottom
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  // Close the fan

     // Right face (x = 0.5)
     0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  // Center vertex
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Front-bottom
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Back-bottom
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Back-top
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Front-top
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Close the fan

     // Top face (y = 0.5)
     0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  // Center vertex
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Front-left
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Front-right
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Back-right
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Back-left
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Close the fan

    // Bottom face (y = -0.5)
    0.0f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  // Center vertex
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Front-left
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Back-left
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Back-right
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Front-right
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f   // Close the fan
    };



    unsigned int 222222222222triangleFanCubeVAO, 2222222222222triangleFanCubeVBO;
    glGenVertexArrays(1, &triangleFanCubeVAO);
    glGenBuffers(1, &triangleFanCubeVBO);

    glBindVertexArray(triangleFanCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleFanCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleFanCube_Vertices), triangleFanCube_Vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);















        //Drawing a Fan cube
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * scaleMatrix;

        // Call the function
        333333333333drawTriangleFanCube(333333333333333triangleFanCubeVAO, lightingShader, model, 0.7f, 0.3f, 0.5f);





















void 44444444444drawTriangleFanCube(unsigned int& 4444444444triangleFanCubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(44444444444444triangleFanCubeVAO);

    glBindVertexArray(44444444444444triangleFanCubeVAO);
    for (int i = 0; i < 6; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, i * 6, 6); // Each face has 6 vertices (1 center + 5 corners)
    }
    glBindVertexArray(0);

}


