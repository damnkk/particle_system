#include"Display.h"
#include"InputManager.h"
#include"Particle.h"
#include<iostream>
#include<string>
#include<thread>
#include<vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


const unsigned int fps = 200;
void limitFPS(unsigned int FPS, double start);


void loadObj(const std::string& filepath,std::vector<float>& vertice,std::vector<unsigned int> & indices)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    // 异常处理
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "读取模型出现错误: " << import.GetErrorString() << std::endl;
        exit(-1);
    }
    // 模型文件相对路径
    std::string rootPath = filepath.substr(0, filepath.find_last_of('/'));

    // 循环生成 mesh
    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* aimesh = scene->mMeshes[i];

        // 我们将数据传递给我们自定义的mesh
        for (int j = 0; j < aimesh->mNumVertices; j++)
        {
            vertice.push_back(aimesh->mVertices[j].x);
            vertice.push_back(aimesh->mVertices[j].y);
            vertice.push_back(aimesh->mVertices[j].z);

        }

        // 传递面片索引
        for (GLuint j = 0; j < aimesh->mNumFaces; j++)
        {
            aiFace face = aimesh->mFaces[j];
            for (GLuint k = 0; k < face.mNumIndices; k++)
            {
                indices.push_back(face.mIndices[k]);
            }
        }
    }

}






int main()
{
    std::ios_base::sync_with_stdio(false); // Faster cout for debugging

    Display display;


    Camera camera;

    Shader shader("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");

    std::string renderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    std::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "Version: " << version << "\n";

    std::vector<Particle> particles;

    for (unsigned int i = 0; i < Particle::MAX_PARTICLES; i++)
    {
        particles.push_back(Particle());
    }

    display.setBackgroundColour(0.055f, 0.067f, 0.067f, 1.0f);

    double deltaTime = 0.0f;
    double lastFrame = glfwGetTime();
    double oldXPos = 0;
    double oldYPos = 0;
    double xPos = 400;
    double yPos = 300;
    // int numFrames = 0;

    std::vector<float> vertice;
    std::vector<unsigned int> indices;

    loadObj("models/Stanford Bunny.obj", vertice, indices);

    Mesh mesh(vertice,indices);

    while (!glfwWindowShouldClose(display.getWindow()))
    {
        double currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;

        camera._speed= 20.0f * static_cast<float>(deltaTime);

        glfwGetCursorPos(display.getWindow(), &xPos, &yPos);

        InputManager::processKeyPress(display.getWindow(), camera);
        InputManager::processMouseMove(display.getWindow(), xPos, yPos, oldXPos, oldYPos, camera);

        oldXPos = xPos;
        oldYPos = yPos;

        display.update(shader, camera, deltaTime, particles,mesh);
        display.render();

        lastFrame = currentFrame;

        //limitFPS(fps, currentFrame);
    }

    return 0;
}

// Thread sleeps so that only a max of 'FPS' frames are drawn per second
void limitFPS(unsigned int FPS, double start)
{
    auto timeToSleep = static_cast<std::chrono::milliseconds>(static_cast<long long>((1000 / FPS - (glfwGetTime() * 1000 - start * 1000))));
    std::this_thread::sleep_for(timeToSleep);
}