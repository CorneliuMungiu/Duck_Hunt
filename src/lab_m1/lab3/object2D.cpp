#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill) {

    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),//0
        VertexFormat(corner + glm::vec3(length / 2,length / 2,0),color),//1
        VertexFormat(corner + glm::vec3(0,length / 2,0),color),//2
        VertexFormat(corner + glm::vec3(length,length / 2,0),color),//3
        VertexFormat(corner + glm::vec3(length,(3*length)/4,0),color),//4
        VertexFormat(corner + glm::vec3(length/2,(3*length)/4,0),color),//5
        VertexFormat(corner + glm::vec3(0,(3*length)/4,0),color),//6
        VertexFormat(corner + glm::vec3(length/4,length,0),color),//7
        VertexFormat(corner + glm::vec3((3*length)/4,length,0),color),//8

    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        indices = { 0, 3, 4, 8, 5, 7, 6, 2 };
        heart->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices = {0,1,2,
                   0,3,1,
                   1,3,4,
                   1,4,5,
                   2,1,5,
                   2,5,6,
                   6,5,7,
                   5,4,8 };
    }

    heart->InitFromData(vertices, indices);
    return heart;
}
Mesh* object2D::CreateBullet(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill) {
    
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner,color1),//0
        VertexFormat(corner + glm::vec3(length, 0, 0),color1),//1
        VertexFormat(corner + glm::vec3(length, 2 * length, 0),color1),//2
        VertexFormat(corner + glm::vec3(0, 2 * length,0), color1),//3
        VertexFormat(corner + glm::vec3(length / 2, 3 * length, 0),color2),//4
        VertexFormat(corner + glm::vec3(length, 2 * length, 0),color2),//5
        VertexFormat(corner + glm::vec3(0, 2 * length,0), color2),//6
        VertexFormat(corner + glm::vec3(length / 2, 3 * length, 0),color1),//7
    };

    Mesh* bullet = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        indices = { 0,1,2,7,3 };
        bullet->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices = {0,1,2,
                   0,2,3,
                   6,5,4};
    }
    bullet->InitFromData(vertices, indices);
    return bullet;

}



Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill) {

    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };
    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}


Mesh* object2D::CreateTriangleWing(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(abs(length/2), 1.25 * length , 0), color),
        VertexFormat(corner + glm::vec3(abs(length) ,0, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0,1,2};

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }


    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateTriangleBody(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, length , 0), color),
        VertexFormat(corner + glm::vec3(2 * length ,length / 2, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0,1,2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }


    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    float x = center[0];
    float y = center[1];
    int triangleAmount = 100;
    float twicePi = 2 * M_PI;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    for (int i = 0; i < triangleAmount; i++) {
        vertices.push_back(VertexFormat (center + glm::vec3((radius * cos(i * twicePi / triangleAmount)),(radius * sin(i*twicePi/triangleAmount)), 0), color));
        indices.push_back(i);
    }
    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }


    circle->InitFromData(vertices, indices);
    return circle;
}
