// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

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
void animacionR();


// Camara
Camera camera( glm::vec3( 0.0f, 5.0f, 20.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

//Declaracion de las variables
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool anim;

//Declaracion variables animacion sencilla silla escritorio
float transilla = 0.0f; 
bool acsilla;
float rotsilla = 0.0f;

//Declaracio variables animacion sencilla patineta
float transpat = 0.0f;
float rotpat = 0.0f;
bool acpat;

//Declaracion variables regadera
float rotreg = 0.0f;
float transreg = 0.0f;
bool acreg;

//Declaracion de variables animacion sencilla libro
float transBookX = 0.0f;
float transBookY = 0.0f;
float transBookZ = 0.0f;
float rotBook = 0.0f;
bool acbook;

// Declaracion variables animacion Regadera
float movKitXReg = 0.0;
float movKitYReg = 0.0;
float movKitZReg = 0.0;
float rotKitReg = 0.0;

// variable del tiempo para oscilacion de la regadera
float tiempo;
bool circuitoReg1;

bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;

//Declaracion de variables para juguete raton animacion compleja

float v0y = 0.0;
float v0z = 0.0;
float rotKitRat = 0.0;

//se usaron para implementar tiro parabolico 
bool circuitoRat1;
bool circuitoRat2;

bool recorrido4 = true;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;



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
    

    // Carga de modelos 
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
    Model raton((char*)"Models/Juguete/juguete.obj");
    Model tapete((char*)"Models/Tapete/tapete.obj");
    Model sofa((char*)"Models/Sofa/sofa.obj");
    Model cuadros2((char*)"Models/Cuadro2/cuadros2.obj");
    Model mesita((char*)"Models/Mesita/mesita.obj");
    Model lampara((char*)"Models/Lampara/lampara.obj");
    Model muebletv((char*)"Models/Muebletv/muebletv.obj");
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
        animacionR();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //camara
        shader.Use();
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));



        /*Carga de los modelos dentro de la fachada, usando traslacion, rotacion,
        escalamiento para acomodar todo el entorno*/
      
        //model fachada
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        model = glm::mat4(1);
        fachada.Draw(shader);

        //modelo escritorio 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.759f, 4.631f, -3.53f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.183f, 0.183f, 0.217f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        desk.Draw(shader);

        //modelo cama 
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
       

       /*CARGA MODELOS ANIMACIONES SENCILLAS
       sencillas ya que solo estamos incrementando linealmente*/
        
       //silla de escritorio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.863f + transilla, 4.73f, -4.14f));
        model = glm::rotate(model, glm::radians(90.0f + rotsilla), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.129f, 0.129f, 0.129f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(shader);

        //patineta
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.23f, 4.731f, -8.12f+transpat)); 
        model = glm::rotate(model, glm::radians(rotpat), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.113f, 0.113f, 0.113f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        patin.Draw(shader);

        //libro para animar
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.197f + transBookX, 6.672f + transBookY, -2.662f + transBookZ));
        model = glm::rotate(model, glm::radians(rotBook), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.061f, 0.061f, 0.061f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        libro.Draw(shader);

        //tapete
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.574f, 0.386f, -4.336f));
        model = glm::scale(model, glm::vec3(0.435f, 0.651f, 0.211f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tapete.Draw(shader);

        //sofa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.434f, 0.533f, -5.599f));
        model = glm::scale(model, glm::vec3(0.299f, 0.299f, 0.299f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sofa.Draw(shader);


        //cuadros2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.344f, 2.153f, -6.754f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.166f, 0.166f, 0.166f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadros2.Draw(shader);

        //mesita
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.758f, 0.393f, -5.184f));
        model = glm::scale(model, glm::vec3(0.377f, 0.428f, 0.428f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesita.Draw(shader);

        //lampara
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.456f, 0.357f, -6.215f));
        model = glm::scale(model, glm::vec3(0.632f, 0.627f, 0.632f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lampara.Draw(shader);

        //muebletv
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.574f, 0.386f, -4.336f));
        model = glm::scale(model, glm::vec3(0.435f, 0.651f, 0.211f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        muebletv.Draw(shader);

        //teletv
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.574f, 0.386f, -4.336f));
        model = glm::scale(model, glm::vec3(0.435f, 0.651f, 0.211f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tele.Draw(shader);


        //cuadros3
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.574f, 0.386f, -4.336f));
        model = glm::scale(model, glm::vec3(0.435f, 0.651f, 0.211f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadros3.Draw(shader);

        //puerta
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.574f, 0.386f, -4.336f));
        model = glm::scale(model, glm::vec3(0.435f, 0.651f, 0.211f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puerta.Draw(shader);


        //hamster
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.574f, 0.386f, -4.336f));
        model = glm::scale(model, glm::vec3(0.435f, 0.651f, 0.211f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        hamster.Draw(shader);


        /*CARGA DE MODELOS ANIMACIONES COMPLEJAS */
        //regadera se uso la variable tiempo para que oscile y de vueltas en su eje
        tiempo = glfwGetTime();
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-11.209f, 0.782f, 0.94f) + glm::vec3(movKitXReg, movKitYReg, movKitZReg));
        model = glm::rotate(model, glm::radians(rotKitReg), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.161f, 0.161f, 0.161f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        regadera.Draw(shader);

      
        /*juguete de ratoncito carro
        este se implemento con tiro parabolico con coordenadas v0y y v0z, donde 
        vemos en y max */
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.611f, 4.741f, -10.96f) + glm::vec3(0, v0y, v0z));
        model = glm::rotate(model, glm::radians(rotKitRat), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.047f, 0.047f, 0.047f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        raton.Draw(shader);

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

    //animacion silla de escritorio

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

    //animacion patineta

    if (keys[GLFW_KEY_T]) {
        acpat = !acpat;   
        if (acpat) {
            transpat -= 2.0f;   //translate funcion 
            rotpat -= 45.0f;    //rotate funcion 
        }
        else {
            transpat += 2.0f;  //translate funcion
            rotpat += 45.0f;   //rotate funcion de patineta
        }
    }

    //animacion de libro
    if (keys[GLFW_KEY_Y]) {
        acbook = !acbook;
        if (acbook) {
            transBookX -= 0.5f;   //translate funcion eje Y
            transBookZ -= 0.338;  //translate funcion eje Z
            transBookY -= 0.847;  //translate funcion eje Y
            rotBook += 90.0f;     //rotacion del libro
        }
        else {
            transBookX += 0.5f;
            transBookZ += 0.338;
            transBookY += 0.847;
            rotBook -= 90.0f;
        }
    }

    //animacion regadera de plantas
    if (keys[GLFW_KEY_Z]) {
        if (circuitoReg1)
        {
            circuitoReg1 = false;   //para recorrido 1 
        }
        else
        {
            circuitoReg1 = true;    //se desactiva recorrido
        }
    }


    //animacion ratoncito de juguete
    
    if (keys[GLFW_KEY_X]) {
        if (circuitoRat1)
        {
            circuitoRat1 = false;   //se desactiva recorrido 1
            circuitoRat2 = true;    //se activa recorrido 2 para juguete
        }
        else
        {
            circuitoRat1 = true;    //para que regrese posicion original
            circuitoRat2 = false;
        }
    }
    
}

void animacionR()
{
    // Movimiento de la regadera usando la variable tiempo para oscilar 
    if (circuitoReg1)
    {
        if (recorrido1)
        {
            movKitYReg += 0.5f;       
            if (movKitYReg < 1.5)     
            {
                recorrido1 = false;
                recorrido2 = true;
            }
        }
        if (recorrido2)
        {
            rotKitReg = -60;
            movKitZReg -= 0.5f;
            if (movKitZReg < -2.0)
            {
                recorrido2 = false;
                recorrido3 = true;
            }
        }
        if (recorrido3)
        {
            movKitZReg = sin(tiempo + 5);
            movKitXReg = sin(tiempo);
        }
    }


    //movimiento de ratoncito usando tiro parabolico
    if (circuitoRat1)
    {
        if (recorrido4)
        {
            rotKitRat = 0;
            v0y += 0.5f;
            v0z += 0.5f;
            if (v0z > 1.5 || v0y > 1.5)   //calcule la altura maxima del raton 
            {
                recorrido4 = false;
                recorrido5 = true;
            }
        }
        if (recorrido5)
        {
            v0y -= 0.5f;
            v0z += 0.5f;
            if (v0z > 3.5 || v0y < 0.0)   //altura va auementando cuando cae 
            {
                recorrido5 = false;
                recorrido6 = true;
            }
        }
    }
    
    if (circuitoRat2)
    {
        if (recorrido6)
        {
            rotKitRat = 180;     //regresando el raton a su posicion inicial
            v0z -= 0.5f;
            if (v0z < 0.5)
            {
                recorrido6 = false;
                recorrido4 = true;
            }
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

