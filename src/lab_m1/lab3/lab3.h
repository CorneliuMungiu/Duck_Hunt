#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"


namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        
        void modify_angular_wing(float deltaTimeSeconds);
        void colisionBorder(float deltaTimeSeconds);
        void hitbox(float deltaTimeSeconds);
        void RenderHeartsAndBullets();
        void dieAnimation(float deltaTimeSeconds);
        void escapeAnimation(float deltaTimeSeconds);

     protected:
        glm::ivec2 resolution;
        float size;
        bool gameOver = false;
        float time;

        glm::mat3 modelMatrix;
        float translateX, translateY;
        float angularStep;
        float angular_wing;
        float speedX;
        float speedY;
        bool dirX;
        bool dirY;
        float birdlen;
        bool isAlive;

        int lives;
        int bullets;
        int killed_count;
        int dificulty;
        int score;
        bool heart1_fill;
        bool heart2_fill;
        bool heart3_fill;

        int mouse_X;
        int mouse_Y;
        int mouseX_crosshair;
        int mouseY_crosshair;

        const glm::vec3 kTextColor = NormalizedRGB(182, 24, 15);
        const glm::vec3 kTextColorSpace = NormalizedRGB(0,0,0);
        const glm::vec3 kBackgroundColor = NormalizedRGB(41, 45, 62);
        gfxc::TextRenderer* textRenderer;
    };
}
