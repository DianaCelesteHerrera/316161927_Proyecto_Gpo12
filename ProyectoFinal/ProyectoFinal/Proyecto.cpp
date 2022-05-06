// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool anim;
float transilla = 0.0f; 
bool acsilla;
float rotsilla = 0.0f;
float transpat = 0.0f;
float rotpat = 0.0f;
bool acpat;
float rotreg = 0.0f;
float transreg = 0.0f;
bool acreg;




int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );
    

    // Load models
    Model fachada((char*)"Models/Fachada/fachada2.obj");
    Model desk((char*)"Models/Desk/desk.obj");
    Model cuadro((char*)"Models/Cuadros/cuadros.obj");
    Model cama((char*)"Models/Bed/bed.obj");
    Model silla((char*)"Models/Silla/silla.obj");
    Model aire((char*)"Models/Aire/aire.obj");
    Model repisa((char*)"Models/Repisa/repisa.obj");
    Model planta((char*)"Models/Planta/planta.obj");
    Model lap((char*)"Models/Laptop/laptop.obj");
    Model patin((char*)"Models/Patineta/patineta.obj");
    Model regadera((char*)"Models/Regadera/regadera.obj");
    Model libro((char*)"Models/Libro/book.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

  
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //model fachada
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        model = glm::mat4(1);
        fachada.Draw(shader);

        ////model desk
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.759f, 4.631f, -3.53f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.183f, 0.183f, 0.217f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        desk.Draw(shader);

        ////model cama
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.228f, 4.761f, -4.335f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.251f, 0.251f, 0.251f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cama.Draw(shader);

        //model cuadros
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.873f, 6.108f, -4.661f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.176f, 0.176f, 0.176f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadro.Draw(shader);

        //silla
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.863f+transilla, 4.73f, -4.14f));
        model = glm::rotate(model, glm::radians(90.0f+rotsilla), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.129f, 0.129f, 0.129f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(shader);

        //aire acondicionado
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.854f, 7.351f, -4.063f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.146f, 0.146f, 0.146f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        aire.Draw(shader);

        //repisa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.825f, 6.216f, -3.482f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.184f, 0.184f, 0.184f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        repisa.Draw(shader);

        //planta
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.007f, 5.85f, -5.125f));
        model = glm::scale(model, glm::vec3(0.11f, 0.11f, 0.11f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        planta.Draw(shader);

        //laptop
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.356f, 5.81f, -4.059f));
        model = glm::scale(model, glm::vec3(0.046f, 0.046f, 0.046f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lap.Draw(shader);
       
        //patineta
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.23f, 4.731f, -8.12f+transpat)); 
        model = glm::rotate(model, glm::radians(rotpat), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.113f, 0.113f, 0.113f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        patin.Draw(shader);

        //regadera
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-9.868f, 0.782f+ transreg, 0.94f));
        model = glm::rotate(model, glm::radians(rotreg), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.161f, 0.161f, 0.161f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        regadera.Draw(shader);

        //libro para animar
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.197f, 6.672f , -2.662f));
        model = glm::scale(model, glm::vec3(0.061f, 0.061f, 0.061f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        libro.Draw(shader);

        ////juguete de ratoncito carro para animar
        //model = glm::mat4(1);
        //model = glm::translate(model, glm::vec3(-3.611f, 4.741f, -10.96f));
        //model = glm::scale(model, glm::vec3(0.047f, 0.047f, 0.047f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //raton.Draw(shader);

        glBindVertexArray(0);

       


        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

    

    if (keys[GLFW_KEY_R]) {
        acsilla = !acsilla;
        if (acsilla) {
            transilla -= 1.0f;
            rotsilla -= 70.0f;
        }
        else {
            transilla += 1.0f;
            rotsilla += 70.0f; 
        }
    }

    if (keys[GLFW_KEY_T]) {
        acpat = !acpat;
        if (acpat) {
            transpat -= 2.0f;
            rotpat -= 45.0f;
        }
        else {
            transpat += 2.0f;
            rotpat += 45.0f; 
        }
    }

    if (keys[GLFW_KEY_Y]) {
        acreg = !acreg;
        if (acreg) {
            transreg -= 1.0f;
            rotreg -= 45.0f;
        }
        else {
            transreg += 1.0f;
            rotreg += 45.0f;
        }
    }
 
 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY =  yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

