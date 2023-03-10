#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

Lab3::Lab3()
{
}


Lab3::~Lab3()
{

}

void Lab3::Init()
{
    //Camera Settings
    {
        window->HidePointer();
        resolution = window->GetResolution();
        auto camera = GetSceneCamera();
        camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
        camera->SetPosition(glm::vec3(0, 0, 50));
        camera->SetRotation(glm::vec3(0, 0, 0));
        camera->Update();
        GetCameraInput()->SetActive(false);
    }

    //Initial Game Settings
    {
        glm::vec3 corner = glm::vec3(0, 0, 0);
        size = 50;
        lives = 3;
        bullets = 3;
        killed_count = 0;
        dificulty = 1;
        score = 0;
        time = 0;

        heart1_fill = true;
        heart2_fill = true;
        heart3_fill = true;
    }

    //Initial bird settings
    {
        //Initial position
        translateX = 50;
        translateY = 100;
        //Initial speed(angle depends on the speedy/speedx ratio)
        speedX = 50;
        speedY = 100;
        //Bird's direction
        dirX = true;
        dirY = true;

        birdlen = (8 * size) / 3;
        isAlive = true;
        angular_wing = 0;
        angularStep = 3;
    }

    //Bird meshes
    {
        glm::vec3 body_corner = glm::vec3(0, 0, 0);
        glm::vec3 body_color = NormalizedRGB(88, 58, 38);
        Mesh* body = object2D::CreateTriangleBody("body", body_corner, size, body_color, true);
        AddMeshToList(body);

        glm::vec3 wing1_corner = body_corner + glm::vec3(size / 2, (3 * size) / 4, 0);
        glm::vec3 wing1_color = NormalizedRGB(88, 58, 38);
        Mesh* wing1 = object2D::CreateTriangleWing("wing1", wing1_corner, size / 2, wing1_color, true);
        AddMeshToList(wing1);

        glm::vec3 wing2_corner = body_corner + glm::vec3(size / 2, size / 4, 0);
        glm::vec3 wing2_color = NormalizedRGB(88, 58, 38);
        Mesh* wing2 = object2D::CreateTriangleWing("wing2", wing2_corner, -(size / 2), wing2_color, true);
        AddMeshToList(wing2);

        glm::vec3 head_center = body_corner + glm::vec3(2 * size, size / 2, 0);
        glm::vec3 head_color = NormalizedRGB(48, 87, 55);
        Mesh* head = object2D::CreateCircle("head", head_center, size / 2.5, head_color, true);
        AddMeshToList(head);

        glm::vec3 beak_corner = body_corner + glm::vec3(2 * size, size / 2 - size / 6, 0);
        glm::vec3 beak_color = NormalizedRGB(231, 204, 57);
        Mesh* beak = object2D::CreateTriangleBody("beak", beak_corner, size / 3, beak_color, true);
        AddMeshToList(beak);
    }

    //Grass meshes
    {
        glm::vec3 grass_corner = glm::vec3(0, 0, 0);
        glm::vec3 grass_color = NormalizedRGB(94, 133, 9);
        Mesh* grass = object2D::CreateRectangle("grass", grass_corner, resolution.x, resolution.y / 5, grass_color, true);
        AddMeshToList(grass);
    }

    //Hud meshes
    {
        glm::vec3 heart1_corner = glm::vec3(resolution.x / 80, resolution.y / 20, 0);
        glm::vec3 heart_color = NormalizedRGB(227, 27, 35);
        Mesh* heart1 = object2D::CreateHeart("heart1", heart1_corner, size, heart_color, true);
        Mesh* heart1_fill = object2D::CreateHeart("heart1_fill", heart1_corner, size, heart_color, false);
        AddMeshToList(heart1);
        AddMeshToList(heart1_fill);

        glm::vec3 heart2_corner = glm::vec3(resolution.x / 80 + size + 10, resolution.y / 20, 0);
        Mesh* heart2 = object2D::CreateHeart("heart2", heart2_corner, size, heart_color, true);
        Mesh* heart2_fill = object2D::CreateHeart("heart2_fill", heart2_corner, size, heart_color, false);
        AddMeshToList(heart2);
        AddMeshToList(heart2_fill);

        glm::vec3 heart3_corner = glm::vec3(resolution.x / 80 + 2 * size + 2 * 10, resolution.y / 20, 0);
        Mesh* heart3 = object2D::CreateHeart("heart3", heart3_corner, size, heart_color, true);
        Mesh* heart3_fill = object2D::CreateHeart("heart3_fill", heart3_corner, size, heart_color, false);
        AddMeshToList(heart3);
        AddMeshToList(heart3_fill);

        glm::vec3 bullet1_corner = heart3_corner + glm::vec3(100, 0, 0);
        glm::vec3 bullet_color = NormalizedRGB(255, 152, 0);
        glm::vec3 bullet_color1 = NormalizedRGB(0, 0, 0);
        Mesh* bullet1 = object2D::CreateBullet("bullet1", bullet1_corner, size / 3, bullet_color, bullet_color1, true);
        Mesh* bullet1_fill = object2D::CreateBullet("bullet1_fill", bullet1_corner, size / 3, bullet_color, bullet_color1, false);
        AddMeshToList(bullet1);
        AddMeshToList(bullet1_fill);

        glm::vec3 bullet2_corner = bullet1_corner + glm::vec3(50, 0, 0);
        Mesh* bullet2 = object2D::CreateBullet("bullet2", bullet2_corner, size / 3, bullet_color, bullet_color1, true);
        Mesh* bullet2_fill = object2D::CreateBullet("bullet2_fill", bullet2_corner, size / 3, bullet_color, bullet_color1, false);
        AddMeshToList(bullet2);
        AddMeshToList(bullet2_fill);

        glm::vec3 bullet3_corner = bullet2_corner + glm::vec3(50, 0, 0);
        Mesh* bullet3 = object2D::CreateBullet("bullet3", bullet3_corner, size / 3, bullet_color, bullet_color1, true);
        Mesh* bullet3_fill = object2D::CreateBullet("bullet3_fill", bullet3_corner, size / 3, bullet_color, bullet_color1, false);
        AddMeshToList(bullet3);
        AddMeshToList(bullet3_fill);

        glm::vec3 crosshair_corner = glm::vec3(0, 0, 0);
        glm::vec3 crosshair_color = NormalizedRGB(0, 0, 0);
        Mesh* crosshair = object2D::CreateSquare("crosshair", crosshair_corner, 10, crosshair_color, true);
        AddMeshToList(crosshair);
    }

    // Create the text render object
    {
        glm::ivec2 resolution = window->GetResolution();
        textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

        textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);
    }
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.0f, 0.5f, 1.0f, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x , resolution.y);

}


/* Rotates the bird when it hits the border */
void Lab3::colisionBorder(float deltaTimeSeconds) {
    //Quadrant 1 of the trigonometric circle
    if (dirX && dirY) {
        translateX += deltaTimeSeconds * speedX;
        translateY += deltaTimeSeconds * speedY;
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(atan(speedY / speedX));
        
        //If it hits the top border
        if (translateY > resolution.y - (birdlen * sin(atan(speedY / speedX)))) {
            dirX = true;
            dirY = false;
        }
        //If it hits the right border
        if (translateX > resolution.x - (birdlen * cos(atan(speedY / speedX)))) {
            dirX = false;
            dirY = true;
        }
    }
    //Quadrant 4 of the trigonometric circle
    else if (dirX && !dirY) {
        translateX += deltaTimeSeconds * speedX;
        translateY -= deltaTimeSeconds * speedY;
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(atan(-speedY / speedX));
        
        //If it hits the bottom border
        if (translateY < (birdlen * sin(atan(speedY / speedX)))) {
            dirX = true;
            dirY = true;
        }
        //If it hits the right border
        if (translateX > resolution.x - (birdlen * cos(atan(-speedY / speedX)))) {
            dirX = false;
            dirY = false;
        }
    }
    //Quadrant 2 of the trigonometric circle
    else if (!dirX && dirY) {
        translateX -= deltaTimeSeconds * speedX;
        translateY += deltaTimeSeconds * speedY;
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(M_PI + atan(speedY / -speedX));
        
        //If it hits the left border
        if (translateX < (birdlen * cos(atan(speedY / speedX)))) {
            dirX = true;
            dirY = true;
        }
        //If it hits the top borders
        if (translateY > resolution.y - (birdlen * sin(atan(speedY / speedX)))) {
            dirX = false;
            dirY = false;
        }
    }
    //Quadrant 3 of the trigonometric circle
    else if (!dirX && !dirY) {
        translateX -= deltaTimeSeconds * speedX;
        translateY -= deltaTimeSeconds * speedY;
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(M_PI + (M_PI / 2) + atan(speedX / -speedY));

        //If it hits the left border
        if (translateX < (birdlen * cos(atan(speedY / speedX)))) {
            dirX = true;
            dirY = false;
        }
        //If it hits the bottom border
        if (translateY < (birdlen * sin(atan(speedY / speedX)))) {
            dirX = false;
            dirY = true;
        }

    }
}

/* Changes the angle of rotation of the wings to move cyclically */
void Lab3::modify_angular_wing(float deltaTimeSeconds) {
    static int direction = 1;
    if (angular_wing > 0.3) {
        direction = -1;
    }
    if (angular_wing < -0.3) {
        direction = 1;
    }
    angular_wing += direction * deltaTimeSeconds * angularStep;
}

/* The bird's death animation is applied. The score is updated and a new bird is generated. */
void Lab3::dieAnimation(float deltaTimeSeconds) {
    translateY -= deltaTimeSeconds * 500;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(3 * M_PI / 2);

    if (translateY < -100) {

        //Since the bird always starts from the grass, the direction angle can only be in quadrants 1 and 2
        {
            int aux = rand() % 2;
            if (aux == 0)
                dirX = false;
            else
                dirX = true;
            dirY = true;
        }

        //The new coordinates of the bird's appearance and the new speed on x and y are generated
        {
            translateX = rand() % (resolution.x / 2) + (resolution.x / 4);
            translateY = 0;
            speedX = rand() % 50 + (200 + dificulty * 50);
            speedY = rand() % 50 + (100 + dificulty * 50);
        }

        /* The modelMatrix and the number of bullets are reset.The scoreand difficulty increase
        depending on the number of birds killed up to this moment */
        {
            modelMatrix = glm::mat3(1);
            colisionBorder(deltaTimeSeconds);
            isAlive = true;
            bullets = 3;
            killed_count++;
            if (killed_count == 5) {
                killed_count = 0;
                if (dificulty < 9)
                    dificulty++;
            }
            score += dificulty * (killed_count + 1);
            time = 0;
        }
    }
}

/* The bird's escape animation is applied.The bullet count and time are reset. The number of lives is reduced */
void Lab3::escapeAnimation(float deltaTimeSeconds) {
    isAlive = false;
    translateY += deltaTimeSeconds * 500;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(M_PI / 2);

    if (translateY > resolution.y + 100) {
        // Since the bird always starts from the grass, the direction angle can only be in quadrants 1 and 2
        {
            int aux = rand() % 2;
            if (aux == 0)
                dirX = false;
            else
                dirX = true;
            dirY = true;
        }

        //The new coordinates of the bird's appearance and the new speed on x and y are generated
        {
            translateX = rand() % (resolution.x / 2) + (resolution.x / 4);
            translateY = 0;
            speedX = rand() % 50 + (200 + dificulty * 50);
            speedY = rand() % 50 + (100 + dificulty * 50);
        }
        //The modelMatrix, time and the number of bullets are reset. The number of lives is reduced
        {
            modelMatrix = glm::mat3(1);
            colisionBorder(deltaTimeSeconds);
            isAlive = true;
            lives--;
            bullets = 3;
            time = 0;
        }
    }
}

/* Check if when the gun was fired it hit the bird's hitbox */
void Lab3::hitbox(float deltaTimeSeconds) {
    //Quadrant 1 of the trigonometric circle
    if (dirX && dirY) {
        //Limits of hitbox
        float limMaxX = translateX + (birdlen * cos(atan(speedY / speedX)));
        float limMinX = translateX - (size * cos(M_PI_2 - atan(speedY / speedX)));
        float limMinY = translateY;
        float limMaxY = translateY + (birdlen * sin(atan(speedY / speedX)));

        //If the bird is hit
        if (mouse_X < limMaxX && mouse_X > limMinX && mouse_Y > limMinY && mouse_Y < limMaxY && bullets >= 0) {
            mouse_X = -1;
            mouse_Y = -1;
            isAlive = false;
        }
    }
    //Quadrant 4 of the trigonometric circle
    else if (dirX && !dirY) {
        //Limits of hitbox
        float limMinY = translateY - (birdlen * cos(M_PI_2 - atan(speedY / speedX)));
        float limMaxY = translateY + (size * cos(-atan(speedY / speedX)));
        float limMinX = translateX;
        float limMaxX = translateX + (birdlen * sin(M_PI_2 - atan(speedY/ speedY)));

        //If the bird is hit
        if (mouse_X < limMaxX && mouse_X > limMinX && mouse_Y > limMinY && mouse_Y < limMaxY && bullets >= 0) {
            mouse_X = -1;
            mouse_Y = -1;
            isAlive = false;
        }
    }
    //Quadrant 2 of the trigonometric circle
    else if (!dirX && dirY) {
        //Limits of hitbox
        float limMaxX = translateX;
        float limMinX = translateX - (birdlen * sin(M_PI_2 - atan(speedY / speedX)));
        float limMinY = translateY - (size * sin(M_PI_2 - atan(speedY/speedX)));
        float limMaxY = translateY + (birdlen * cos(M_PI_2 - atan(speedY / speedX)));

        //If the bird is hit
        if (mouse_X < limMaxX && mouse_X > limMinX && mouse_Y > limMinY && mouse_Y < limMaxY && bullets >= 0) {
            mouse_X = -1;
            mouse_Y = -1;
            isAlive = false;
        }
    }
    //Quadrant 3 of the trigonometric circle
    else if (!dirX && !dirY) {
        //Limits of hitbox
        float limMaxX = translateX + (size * cos(M_PI_2 - atan(speedY / speedX)));
        float limMinX = translateX - (birdlen * cos(- atan(speedY / speedX)));
        float limMinY = translateY - (birdlen * sin(atan(speedY / speedX)));
        float limMaxY = translateY;

        //If the bird is hit
        if (mouse_X < limMaxX && mouse_X > limMinX && mouse_Y > limMinY && mouse_Y < limMaxY && bullets >= 0) {
            mouse_X = -1;
            mouse_Y = -1;
            isAlive = false;
        }
    }
}

void Lab3::RenderHeartsAndBullets() {
    if (lives == 3) {
        RenderMesh2D(meshes["heart1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart3"], shaders["VertexColor"], glm::mat3(1));
    }
    else if (lives == 2) {
        RenderMesh2D(meshes["heart1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart3_fill"], shaders["VertexColor"], glm::mat3(1));
    }
    else if (lives == 1) {
        RenderMesh2D(meshes["heart1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart2_fill"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart3_fill"], shaders["VertexColor"], glm::mat3(1));
    }
    else if (lives <= 0) {
        RenderMesh2D(meshes["heart1_fill"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart2_fill"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["heart3_fill"], shaders["VertexColor"], glm::mat3(1));
    }

    if (bullets == 3) {
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet3"], shaders["VertexColor"], glm::mat3(1));
    }
    else if (bullets == 2) {
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet3_fill"], shaders["VertexColor"], glm::mat3(1));
    }
    else if (bullets == 1) {
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet2_fill"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet3_fill"], shaders["VertexColor"], glm::mat3(1));
    }
    else if (bullets <= 0) {
        RenderMesh2D(meshes["bullet1_fill"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet2_fill"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet3_fill"], shaders["VertexColor"], glm::mat3(1));
    }
}


void Lab3::Update(float deltaTimeSeconds)
{
    //Crosshair
    RenderMesh2D(meshes["crosshair"], shaders["VertexColor"], transform2D::Translate(mouseX_crosshair - 5,mouseY_crosshair - 5));
    time += deltaTimeSeconds;

    //As long as the player has lives
    if (lives >= 0) {

        textRenderer->RenderText("Score: " + to_string(score), resolution.x / 40, resolution.y / 13, 1, kTextColorSpace);
        textRenderer->RenderText("Dificulty: " + to_string(dificulty), resolution.x/40, resolution.y / 10, 1, kTextColorSpace);
        modelMatrix = glm::mat3(1);
        
        if (time < 5 && bullets >= 0) {
           //If bird is alive
            if (isAlive) {
                //Translate and rotate the bird if necessary
                colisionBorder(deltaTimeSeconds);
                //Check if player hits the hitbox
                hitbox(deltaTimeSeconds);
            }
            //If the bird is not alive, it means that the player shot the bird, so the death animation is applied
            else {
                time = 0;
                dieAnimation(deltaTimeSeconds);
            } 
        }
        // If the bird has not been shot for 5 seconds or the player has spent all the bullets
        else {
            escapeAnimation(deltaTimeSeconds);
        }
        
        //World and Hud Render
        {
            RenderHeartsAndBullets();
            RenderMesh2D(meshes["grass"], shaders["VertexColor"], glm::mat3(1));
        }

        //Bird Render
        {
            RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
        }

        //Wing movement Render
        {
            glm::mat3 tmpModelMatrix = modelMatrix;
            modify_angular_wing(deltaTimeSeconds);
            modelMatrix *= transform2D::Translate(size / 2 + size / 4, (3 * size) / 4);
            modelMatrix *= transform2D::Rotate(angular_wing);
            modelMatrix *= transform2D::Translate(-(size / 2 + size / 4), -((3 * size) / 4));
            RenderMesh2D(meshes["wing1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = tmpModelMatrix;

            tmpModelMatrix = modelMatrix;
            modelMatrix *= transform2D::Translate(size / 2 + size / 4, size / 4);
            modelMatrix *= transform2D::Rotate(-angular_wing);
            modelMatrix *= transform2D::Translate(-(size / 2 + size / 4), -(size / 4));
            RenderMesh2D(meshes["wing2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = tmpModelMatrix;
        }

    }
    //If all lives were lost
    else {
        //GAMEOVER Screen
        gameOver = true;
        textRenderer->RenderText("GAME OVER", resolution.x / 3, resolution.y / 2, 3, kTextColor);
        textRenderer->RenderText("Press space to try again", resolution.x / 3, resolution.y / 1.5, 2, kTextColorSpace);
    }

    mouse_X = -1;
    mouse_Y = -1;

}


void Lab3::FrameEnd()
{
}



void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    //If game is over press space to try again
    if (key == GLFW_KEY_SPACE && gameOver) {
        lives = 3;
        score = 0;
        dificulty = 1;
        gameOver = false;
    }
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    mouseX_crosshair = mouseX;
    mouseY_crosshair = resolution.y - mouseY;
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    mouse_X = mouseX;
    mouse_Y = resolution.y - mouseY;
    bullets--;
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
