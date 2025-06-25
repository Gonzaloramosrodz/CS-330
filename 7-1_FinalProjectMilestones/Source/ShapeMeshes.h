#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShapeMeshes
{
public:
    ShapeMeshes();
    ~ShapeMeshes();

    void LoadPlaneMesh();
    void LoadCubeMesh();
    void LoadSphereMesh();
    void LoadCylinderMesh();
    void LoadTorusMesh(float thickness = 0.2f);
    void LoadConeMesh();

    void DrawPlaneMesh();
    void DrawCubeMesh();
    void DrawSphereMesh();
    void DrawCylinderMesh(bool bDrawTop = true, bool bDrawBottom = true, bool bDrawSides = true);
    void DrawTorusMesh();
    void DrawConeMesh(bool bDrawBottom = true);

private:
    GLuint m_planeVAO, m_cubeVAO, m_sphereVAO, m_cylinderVAO, m_torusVAO, m_coneVAO;
    GLuint m_planeVBO, m_cubeVBO, m_sphereVBO, m_cylinderVBO, m_torusVBO, m_coneVBO;
    bool m_bMemoryLayoutDone;
};
