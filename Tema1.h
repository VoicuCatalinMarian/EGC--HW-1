#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);
        void EnemyMovement(float deltaTimeSeconds, glm::mat3 visMatrix, int &k, int &l, int *hit_count);
        void enemy_movement_aux(float deltaTimeSeconds, glm::mat3 visMatrix, int &k, int &l, int *hit_count);
        void ProjectileMovement(float deltaTimeSeconds, glm::mat3 visMatrix, int &k, int &l, int *hit_count);
        void projectile_movement_aux(float deltaTimeSeconds, glm::mat3 visMatrix, int &k, int &l, int *hit_count);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix;

        float rectangleWidth = 60;
        float rectangleLength = 440;
        float squareSide = 120;

        float diamondHeight = 100;
        float diamondWidth = 50;
        float starSide = 20;
        float squareSide_health = 80;

        float enemySide = 32;
        float projectileSide = 40;

        float spawn_time;
        int k, l;

        float enemy_translateX[4] = { 1300, 1300, 1300, 1300 }, enemy_translateY[3] = { 60, 220, 380 };
        float enemy_scaleX[4] = { 1, 1, 1, 1 }, enemy_scaleY[4] = { 1, 1, 1, 1 };
        float enemy_cx, enemy_cy;

        float projectile_translateX[4] = { 200, 200, 200, 200 }, projectile_translateY[3] = { 50, 210, 370 };
        float projectile_rotate[4] = { 0, 0, 0, 0 };
        float projectile_cx, projectile_cy;

        float diamond_scaleX[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 }, diamond_scaleY[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        float diamond_cx, diamond_cy;

        int hit_count[4]{};
        int star_count;
        int lives_count;

        int check[4]{};
        int render_diamond[9][4]{};

        int mouse_translateX, mouse_translateY;
    };
}
