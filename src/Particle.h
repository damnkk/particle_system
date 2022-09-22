#pragma once
#include "Mesh.h"
#include <glm.hpp>
#include <vector>

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color()
    {
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
        a = 1.0f;
    }

    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {}

    Color& operator=(const Color& rhs)
    {
        if (this != &rhs)
        {
            r = rhs.r;
            g = rhs.g;
            b = rhs.b;
            a = rhs.a;
        }
        return *this;
    }
};


struct Particle
{
    static const unsigned int MAX_PARTICLES;

    static Mesh& MeshInstance(); // Each particle will have the same mesh data
    static Mesh mesh;
    void load();

    const float SLOW = 0.004f;
    const float NORMAL = 0.1f;
    const float FAST = 1.0f;

    float speed;
    float life;
    float fade;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 gravity;
    glm::mat4 model;

    Color color;

    Particle();
    Particle(glm::vec3 pos, glm::vec3 vel, float fade, Color colour);
    ~Particle() = default;

    void update(double elapsedTime);



    static void draw(Mesh &mesh);

    Particle& operator=(const Particle& rhs)
    {
        if (this != &rhs)
        {
            speed = rhs.speed;
            life = rhs.life;
            fade = rhs.fade;
            position = rhs.position;
            velocity = rhs.velocity;
            gravity = rhs.gravity;
            model = rhs.model;
            color = rhs.color;
        }
        return *this;
    }
};

//Mesh Particle::mesh;



