#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <algorithm>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "fpcontrols.h"
#include "mnt.h"

#include "glm/gtx/string_cast.hpp"

using namespace std;


int main()
{
    /////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


    /////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //définition de la taille de la fenêtre
    int width = 1000;
    int height = 1000;

    //On récupère les dimensions de l'écran pour créer la fenètre
    /*GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);*/

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_API", NULL, NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



    /////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

    /////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


    /////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader("E:/opengl/projet_opengl_tp/projet_opengl_tp/shaders/SimpleVertexShader.vertexshader", "E:/opengl/projet_opengl_tp/projet_opengl_tp/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

    /////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

    /////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    FPControls controls(window, &cam);

    /////////////////////////Création MNT/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "loading" << endl;
    // Loading my MNT
    string mntPath = "height_map.jpg";
    const char* cstr = mntPath.c_str();
    MNT myMNT = MNT(cstr);
    int mntWidth = (int)myMNT.MNTWidth();
    int mntHeight = (int)myMNT.MNTHeight();
    cout << "myMNT width: " << myMNT.MNTWidth() << endl;
    cout << "myMNT height: " << myMNT.MNTHeight() << endl;

    // Generate coordinates
    myMNT.generateTerrainCoordinates();
    vector<glm::vec3> coord = myMNT.getCoordinates();
    cout << "coord size: " << coord.size() << endl;
    cout << "coord size: " << glm::to_string(coord.at(0)) << endl;
    cout << "coord size: " << glm::to_string(coord.at(100)) << endl;
    cout << "coord size: " << glm::to_string(coord.at(200)) << endl;

    // Create vertex buffer 
    cout << "Create vertex buffer " << endl;
    vector<glm::vec3> g_vertex_buffer_data = myMNT.generateVertexBufferMNT();

    // Create uv buffer
    cout << "create uv buffer" << endl;
    vector<glm::vec2> g_uv_buffer_data = myMNT.generateUVBufferMNT(g_vertex_buffer_data.size());
    cout << "uv buffer data size: " << g_uv_buffer_data.size() << endl;

    // Create MNT object
    Object oMNT(g_vertex_buffer_data, g_uv_buffer_data, "E:/opengl/projet_opengl_tp/projet_opengl_tp/textures/green.jpg");
    oMNT.rotationAngles = glm::vec3(0, 0, 0);

    /////////////////////////Création Cube/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Create vertex buffer 
    vector<glm::vec3> g_vertex_buffer_data_o = {
        glm::vec3(-1.0f,-1.0f,-1.0f), // triangle 1 : begin
        glm::vec3(-1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f), // triangle 1 : end
        glm::vec3(1.0f, 1.0f,-1.0f), // triangle 2 : begin
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f), // triangle 2 : end
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f,-1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f,-1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f,-1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f,-1.0f, 1.0f)
    };

    // Create uv buffer
    vector<glm::vec2> g_uv_buffer_data_o = {
        glm::vec2(0.000059f, 1.0f - 0.000004f),
        glm::vec2(0.000103f, 1.0f - 0.336048f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(1.000023f, 1.0f - 0.000013f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.999958f, 1.0f - 0.336064f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(0.667969f, 1.0f - 0.671889f),
        glm::vec2(1.000023f, 1.0f - 0.000013f),
        glm::vec2(0.668104f, 1.0f - 0.000013f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.000059f, 1.0f - 0.000004f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.336098f, 1.0f - 0.000071f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(1.000004f, 1.0f - 0.671847f),
        glm::vec2(0.999958f, 1.0f - 0.336064f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.668104f, 1.0f - 0.000013f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.667979f, 1.0f - 0.335851f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.668104f, 1.0f - 0.000013f),
        glm::vec2(0.336098f, 1.0f - 0.000071f),
        glm::vec2(0.000103f, 1.0f - 0.336048f),
        glm::vec2(0.000004f, 1.0f - 0.671870f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(0.000103f, 1.0f - 0.336048f),
        glm::vec2(0.336024f, 1.0f - 0.671877f),
        glm::vec2(0.335973f, 1.0f - 0.335903f),
        glm::vec2(0.667969f, 1.0f - 0.671889f),
        glm::vec2(1.000004f, 1.0f - 0.671847f),
        glm::vec2(0.667979f, 1.0f - 0.335851f)
    };

    // Create object - cube
    Object oObj(g_vertex_buffer_data_o, g_uv_buffer_data_o, "E:/opengl/projet_opengl_tp/projet_opengl_tp/textures/t0010_0.png");

    /////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Initialization of camera position
    float alti = (float)myMNT.getAltitude(246, 246, 1);
    cam.position = glm::vec3(246.0f, alti + 2.0f, 246.0f);

    // MVP matrix
    cam.computeMatrices(width, height);
    glm::mat4 mo = oObj.getModelMatrix(); // for the moving cube
    glm::mat4 mMNT = oMNT.getModelMatrix(); // for the digital elevation model

    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();

    glm::mat4 mvpObj = p * v * mo; // for the moving cube
    glm::mat4 mvpMNT = p * v * mMNT; // for the digital elevation model


    shader.setUniformMat4f("MVP", mvpObj);
    shader.setUniformMat4f("MVP", mvpMNT);


    /////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    // Time and coordinates initialization for the moving cube
    float t = 0.0;
    int xObj = 314;
    int yObj = 264;
    int hObj = (int) myMNT.getAltitude(xObj, yObj, 1);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        oObj.rotationAngles.y = currentTime;
        
        // coordinates of the moving cube
        oObj.position = oObj.moveObjectPosition(t,xObj, yObj, hObj) ;
        t += deltaTime/2;
        xObj = oObj.position.x;
        yObj = oObj.position.z;
        hObj = (int)myMNT.getAltitude((int)xObj, (int)yObj, 1) + 1;

        // Makes sure that the camera always stays at a human eye level
        cam.position.y = (int)myMNT.getAltitude((int)cam.position.x, (int)cam.position.z, 1) + 5;

        
        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();


        // Avoid the camera to go away from the Digital elevation model
        if (cam.position.x < 0) {
            cam.position.x = 0;
        }
        else if (cam.position.x > mntWidth) {
            cam.position.x = 528;
        }
        else if (cam.position.z < 0) {
            cam.position.z = 0;
        }
        else if (cam.position.z > mntHeight) {
            cam.position.z = 528;
        }

        ////////////////On commence par vider les buffers///////////////
        renderer.Clear();

        mMNT = oMNT.getModelMatrix();
        mvpMNT = p * v * mMNT;
        shader.setUniformMat4f("MVP", mvpMNT);
        renderer.Draw(va, oMNT, shader);

        mo = oObj.getModelMatrix();
        mvpObj = p * v * mo;
        shader.setUniformMat4f("MVP", mvpObj);
        renderer.Draw(va, oObj, shader);

        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();





    return 0;

}