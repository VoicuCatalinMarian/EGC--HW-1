#include "Tema1.h"

#include <vector>
#include <iostream>

#include "transform2D.h"
#include "object2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    rectangleWidth = 60;
    rectangleLength = 440;
    squareSide = 120;

    diamondHeight = 100;
    diamondWidth = 50;
    starSide = 20;
    squareSide_health = 80;

    enemySide = 32;
    projectileSide = 40;
    
    spawn_time = 0;

    star_count = 5;
    lives_count = 3;

    enemy_cx = corner.x + enemySide * 0.875f;
    enemy_cy = corner.y + enemySide * 0.625f;

    projectile_cx = corner.x + projectileSide * 0.6f;
    projectile_cy = corner.y + projectileSide * 0.75f;

    diamond_cx = corner.x + diamondWidth * 0.5f;
    diamond_cy = corner.y + diamondHeight * 0.5f;


    Mesh* rectangle_scene = object2D::CreateRectangle("rectangle_scene", corner, rectangleWidth, rectangleLength, glm::vec3(0.8f, 0, 0));
    AddMeshToList(rectangle_scene);

    Mesh* square_scene = object2D::CreateSquare("square_scene", corner, squareSide, glm::vec3(0.25f, 0.9f, 0.4f));
    AddMeshToList(square_scene);

    Mesh* square_gui = object2D::CreateSquareEmpty("square_gui", corner, squareSide, glm::vec3(0, 0, 0));
    AddMeshToList(square_gui);

    Mesh* star_count = object2D::CreateStar("star_count", corner, starSide, glm::vec3(0.6f, 0.6f, 0.6f));
    AddMeshToList(star_count);

    Mesh* square_health = object2D::CreateSquare("square_health", corner, squareSide_health, glm::vec3(0.8f, 0, 0));
    AddMeshToList(square_health);

    glm::vec3 color[4] = { glm::vec3(1, 0.35f, 0), glm::vec3(0, 0.35f, 1), glm::vec3(1, 0.8f, 0), glm::vec3(0.65f, 0, 1) };
    Mesh* diamond[4]{};
    for (int i = 0; i < 4; i++)
    {
        diamond[i] = object2D::CreateDiamond("diamond" + to_string(i), corner, diamondHeight, diamondWidth, color[i]);
        AddMeshToList(diamond[i]);
    }

    Mesh* diamond_move[4]{};
    for (int i = 0; i < 4; i++)
    {
        diamond_move[i] = object2D::CreateDiamond("diamond_move" + to_string(i), corner, diamondHeight, diamondWidth, color[i]);
        AddMeshToList(diamond_move[i]);
    }

    Mesh* enemy[4]{};
    for (int i = 0; i < 4; i++)
    {
        enemy[i] = object2D::CreateEnemy("enemy" + to_string(i), corner, enemySide, color[i]);
        AddMeshToList(enemy[i]);
    }

    Mesh* projectile[4]{};
    for (int i = 0; i < 4; i++)
    {
        projectile[i] = object2D::CreateStar("projectile" + to_string(i), corner, projectileSide, color[i]);
        AddMeshToList(projectile[i]);
    }
}

void Tema1::FrameStart()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    if (lives_count > 0)
    {
        DrawScene(glm::mat3(1));

        for (float i = 868; i < 868 + star_count * 40; i += 40)
        {
            float height = 560;
            modelMatrix = glm::mat3(1) * transform2D::Translate(i, height);
            RenderMesh2D(meshes["star_count"], shaders["VertexColor"], modelMatrix);
        }

        for (float i = 860; i < 860 + lives_count * 120; i += 120)
        {
            modelMatrix = glm::mat3(1) * transform2D::Translate(i, 600);
            RenderMesh2D(meshes["square_health"], shaders["VertexColor"], modelMatrix);
        }

        {
            spawn_time += deltaTimeSeconds;
            EnemyMovement(deltaTimeSeconds, glm::mat3(1), k, l, hit_count);
            ProjectileMovement(deltaTimeSeconds, glm::mat3(1), k, l, hit_count);

            if (mouse_translateX != 0 || mouse_translateY != 0)
            {
                for (int i = 0; i < 4; i++)
                    if (check[i])
                    {
                        modelMatrix = glm::mat3(1) * transform2D::Translate(mouse_translateX - diamondWidth / 2, (float)resolution.y - mouse_translateY);
                        RenderMesh2D(meshes["diamond_move" + to_string(i)], shaders["VertexColor"], modelMatrix);
                    }
            }

            for (int i = 0; i < 9; i++)
            {
                printf("%d %d %d %d\n", render_diamond[i][0], render_diamond[i][1], render_diamond[i][2], render_diamond[i][3]);
                for (int j = 0; j < 4; j++)
                {
                    if (render_diamond[i][j] == 1)
                    {
                        if (i >= 0 && i <= 2)
                        {
                            modelMatrix = glm::mat3(1) * transform2D::Translate(135 + (float)i * 160, 400);
                            for (int p = 0; p < 4; p++)
                            {
                                if (enemy_translateX[2] <= 135 + (float)i * 160)
                                {
                                    while (diamond_scaleX[i] >= 0)
                                    {
                                        diamond_scaleX[i] -= deltaTimeSeconds;
                                        diamond_scaleY[i] -= deltaTimeSeconds;
                                        modelMatrix = glm::mat3(1) * transform2D::Translate(diamond_cx, diamond_cy)
                                            * transform2D::Scale(diamond_scaleX[i], diamond_scaleY[i])
                                            * transform2D::Translate(-diamond_cx, -diamond_cy);
                                    }
                                    if (diamond_scaleX <= 0)
                                    {
                                        diamond_scaleX[i] = 1;
                                        diamond_scaleY[i] = 1;
                                        render_diamond[i][j] = 0;

                                    }
                                }
                            }
                            RenderMesh2D(meshes["diamond" + to_string(j)], shaders["VertexColor"], modelMatrix);
                        }
                        if (i >= 3 && i <= 5)
                        {
                            modelMatrix = glm::mat3(1) * transform2D::Translate(135 + (float)(i - 3) * 160, 240);
                            for (int p = 0; p < 4; p++)
                            {
                                if (enemy_translateX[1] <= 135 + (float)i * 160)
                                {
                                    while (diamond_scaleX[i] >= 0)
                                    {
                                        diamond_scaleX[i] -= deltaTimeSeconds;
                                        diamond_scaleY[i] -= deltaTimeSeconds;
                                        modelMatrix = glm::mat3(1) * transform2D::Translate(diamond_cx, diamond_cy)
                                            * transform2D::Scale(diamond_scaleX[i], diamond_scaleY[i])
                                            * transform2D::Translate(-diamond_cx, -diamond_cy);
                                    }
                                    if (diamond_scaleX <= 0)
                                    {
                                        diamond_scaleX[i] = 1;
                                        diamond_scaleY[i] = 1;
                                        render_diamond[i][j] = 0;

                                    }
                                }
                            }
                            RenderMesh2D(meshes["diamond" + to_string(j)], shaders["VertexColor"], modelMatrix);
                        }
                        if (i >= 6 && i <= 8)
                        {
                            modelMatrix = glm::mat3(1) * transform2D::Translate(135 + (float)(i - 6) * 160, 80);
                            for (int p = 0; p < 4; p++)
                            {
                                if (enemy_translateX[0] <= 135 + (float)i * 160 || enemy_translateX[3] <= 135 + (float)i * 160)
                                {
                                    while (diamond_scaleX[i] >= 0)
                                    {
                                        diamond_scaleX[i] -= deltaTimeSeconds;
                                        diamond_scaleY[i] -= deltaTimeSeconds;
                                        modelMatrix = glm::mat3(1) * transform2D::Translate(diamond_cx, diamond_cy)
                                            * transform2D::Scale(diamond_scaleX[i], diamond_scaleY[i])
                                            * transform2D::Translate(-diamond_cx, -diamond_cy);
                                    }
                                    if (diamond_scaleX <= 0)
                                    {
                                        diamond_scaleX[i] = 1;
                                        diamond_scaleY[i] = 1;
                                        render_diamond[i][j] = 0;

                                    }
                                }
                            }
                            RenderMesh2D(meshes["diamond" + to_string(j)], shaders["VertexColor"], modelMatrix);
                        }
                    }
                }
            }
        }
    }
    else
    {
        // Game Over
        exit(1);
    }
}



void Tema1::FrameEnd()
{
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
    // Visual Elements

    {
        // Game Scene

        modelMatrix = visMatrix * transform2D::Translate(10, 20);
        RenderMesh2D(meshes["rectangle_scene"], shaders["VertexColor"], modelMatrix);

        for (float i = 100; i <= 420; i += 160)
        {
            for (float j = 20; j <= 340; j += 160)
            {
                modelMatrix = visMatrix * transform2D::Translate(i, j);
                RenderMesh2D(meshes["square_scene"], shaders["VertexColor"], modelMatrix);
            }
        }

    }

    {
        // GUI

        for (float i = 60; i <= 660; i += 200)
        {
            modelMatrix = visMatrix * transform2D::Translate(i, 580);
            RenderMesh2D(meshes["square_gui"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = visMatrix * transform2D::Translate(95, 640);
        RenderMesh2D(meshes["diamond0"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(295, 640);
        RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(495, 640);
        RenderMesh2D(meshes["diamond2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(695, 640);
        RenderMesh2D(meshes["diamond3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(68, 540);
        RenderMesh2D(meshes["star_count"], shaders["VertexColor"], modelMatrix);

        for (float i = 268; i <= 308; i += 40)
        {
            modelMatrix = visMatrix * transform2D::Translate(i, 540);
            RenderMesh2D(meshes["star_count"], shaders["VertexColor"], modelMatrix);
        }

        for (float i = 468; i <= 508; i += 40)
        {
            modelMatrix = visMatrix * transform2D::Translate(i, 540);
            RenderMesh2D(meshes["star_count"], shaders["VertexColor"], modelMatrix);
        }

        for (float i = 668; i <= 748; i += 40)
        {
            modelMatrix = visMatrix * transform2D::Translate(i, 540);
            RenderMesh2D(meshes["star_count"], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::enemy_movement_aux(float deltaTimeSeconds, glm::mat3 vixMatrix, int &k, int &l, int *hit_count)
{
    l = k;
    if (l > 2)
        l -= 3;
    enemy_translateX[k] -= 100 * deltaTimeSeconds;
    modelMatrix = glm::mat3(1) * transform2D::Translate(enemy_translateX[k], enemy_translateY[l])
        * transform2D::Rotate(-6);
    if (hit_count[k] == 3)
    {
        enemy_scaleX[k] -= deltaTimeSeconds;
        enemy_scaleY[k] -= deltaTimeSeconds;
        modelMatrix *= transform2D::Translate(enemy_cx, enemy_cy)
            * transform2D::Scale(enemy_scaleX[k], enemy_scaleY[k])
            * transform2D::Translate(-enemy_cx, -enemy_cy);
        enemy_translateX[k] += 100 * deltaTimeSeconds;
        if (enemy_scaleX[k] <= 0)
        {
            enemy_scaleX[k] = 1;
            enemy_scaleY[k] = 1;
            enemy_translateX[k] = 1300;
            hit_count[k] = 0;
        }
    }
    if (enemy_translateX[k] <= 75)
    {
        modelMatrix *= transform2D::Scale(0, 0);
        enemy_translateX[k] = 1300;
        lives_count--;
    }
    RenderMesh2D(meshes["enemy" + to_string(k)], shaders["VertexColor"], modelMatrix);
}

void Tema1::EnemyMovement(float deltaTimeSeconds, glm::mat3 visMatrix, int &k, int &l, int *hit_count)
{
    if (spawn_time > 1)
    {
        k = 0;
        enemy_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
    if (spawn_time > 3)
    {
        k = 1;
        enemy_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
    if (spawn_time > 5)
    {
        k = 2;
        enemy_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
    if (spawn_time > 7)
    {
        k = 3;
        enemy_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
}

void Tema1::projectile_movement_aux(float deltaTimeSeconds, glm::mat3 visMatrix, int& k, int& l, int* hit_count)
{
    l = k;
    if (l > 2)
        l -= 3;
    projectile_translateX[k] += 200 * deltaTimeSeconds;
    projectile_rotate[k] += 5 * deltaTimeSeconds;
    modelMatrix = glm::mat3(1) * transform2D::Translate(projectile_translateX[k], projectile_translateY[l])
        * transform2D::Translate(projectile_cx, projectile_cy)
        * transform2D::Rotate(-projectile_rotate[k])
        * transform2D::Translate(-projectile_cx, -projectile_cy);
    if (projectile_translateX[k] >= enemy_translateX[k] - 65)
    {
        modelMatrix *= transform2D::Scale(0, 0);
        projectile_translateX[k] = 200;
        projectile_rotate[k] = 0;
        hit_count[k]++;
    }
    RenderMesh2D(meshes["projectile" + to_string(k)], shaders["VertexColor"], modelMatrix);
}

void Tema1::ProjectileMovement(float deltaTimeSeconds, glm::mat3 visMatrix, int &k, int &l, int *hit_count)
{
    if (spawn_time > 1)
    {
        k = 0;
        projectile_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
    if (spawn_time > 3)
    {
        k = 1;
        projectile_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
    if (spawn_time > 5)
    {
        k = 2;
        projectile_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }
    /*if (spawn_time > 7)
    {
        k = 3;
        projectile_movement_aux(deltaTimeSeconds, visMatrix, k, l, hit_count);
    }*/
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    printf("Mouse moved: %d %d\n", mouseX, mouseY);

    mouse_translateX = mouseX;
    mouse_translateY = mouseY;

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (mouseY >= 260 && mouseY <= 380)
        {
            if (mouseX >= 100 && mouseX <= 220)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (render_diamond[0][i] == 1)
                    {
                        render_diamond[0][i] = 0;
                        break;
                    }
                }
            }
            if (mouseX >= 260 && mouseX <= 380)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (render_diamond[1][i] == 1)
                    {
                        render_diamond[1][i] = 0;
                        break;
                    }
                }
            }
            if (mouseX >= 420 && mouseX <= 540)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (render_diamond[2][i] == 1)
                    {
                        render_diamond[2][i] = 0;
                        break;
                    }
                }
            }
        }
        else
            if (mouseY >= 420 && mouseY <= 540)
            {
                if (mouseX >= 100 && mouseX <= 220)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (render_diamond[3][i] == 1)
                        {
                            render_diamond[3][i] = 0;
                            break;
                        }
                    }
                }
                if (mouseX >= 260 && mouseX <= 380)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (render_diamond[4][i] == 1)
                        {
                            render_diamond[4][i] = 0;
                            break;
                        }
                    }
                }
                if (mouseX >= 420 && mouseX <= 540)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (render_diamond[5][i] == 1)
                        {
                            render_diamond[5][i] = 0;
                            break;
                        }
                    }
                }
            }
            else
                if (mouseY >= 580 && mouseY <= 700)
                {
                    if (mouseX >= 100 && mouseX <= 220)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (render_diamond[6][i] == 1)
                            {
                                render_diamond[6][i] = 0;
                                break;
                            }
                        }
                    }
                    if (mouseX >= 260 && mouseX <= 380)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (render_diamond[7][i] == 1)
                            {
                                render_diamond[7][i] = 0;
                                break;
                            }
                        }
                    }
                    if (mouseX >= 420 && mouseX <= 540)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (render_diamond[8][i] == 1)
                            {
                                render_diamond[8][i] = 0;
                                break;
                            }
                        }
                    }
                }
    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        if (mouseY >= 20 && mouseY <= 140)
        {
            if (mouseX >= 60 && mouseX <= 180)
            {
                check[0] = 1;
                check[1] = 0;
                check[2] = 0;
                check[3] = 0;
            }
            if (mouseX >= 260 && mouseX <= 380)
            {
                check[0] = 0;
                check[1] = 1;
                check[2] = 0;
                check[3] = 0;
            }
            if (mouseX >= 460 && mouseX <= 580)
            {
                check[0] = 0;
                check[1] = 0;
                check[2] = 1;
                check[3] = 0;
            }
            if (mouseX >= 660 && mouseX <= 780)
            {
                check[0] = 0;
                check[1] = 0;
                check[2] = 0;
                check[3] = 1;
            }
        }
        else
        {
            check[0] = 0;
            check[1] = 0;
            check[2] = 0;
            check[3] = 0;
        }
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (mouseY >= 260 && mouseY <= 380)
    {
        if (mouseX >= 100 && mouseX <= 220)
        {
            for (int i = 0; i < 4; i++)
            {
                int sum = 0;
                for (int j = 0; j < 4; j++)
                    sum += render_diamond[0][j];
                if (sum == 0)
                {
                    if (check[i] == 1)
                    {
                        render_diamond[0][i] = 1;
                        break;
                    }
                }
            }
        }
        if (mouseX >= 260 && mouseX <= 380)
        {
            for (int i = 0; i < 4; i++)
            {
                int sum = 0;
                for (int j = 0; j < 4; j++)
                    sum += render_diamond[1][j];
                if (sum == 0)
                {
                    if (check[i] == 1)
                    {
                        render_diamond[1][i] = 1;
                        break;
                    }
                }
            }
        }
        if (mouseX >= 420 && mouseX <= 540)
        {
            for (int i = 0; i < 4; i++)
            {
                int sum = 0;
                for (int j = 0; j < 4; j++)
                    sum += render_diamond[2][j];
                if (sum == 0)
                {
                    if (check[i] == 1)
                    {
                        render_diamond[2][i] = 1;
                        break;
                    }
                }
            }
        }
    }
    else
        if (mouseY >= 420 && mouseY <= 540)
        {
            if (mouseX >= 100 && mouseX <= 220)
            {
                for (int i = 0; i < 4; i++)
                {
                    int sum = 0;
                    for (int j = 0; j < 4; j++)
                        sum += render_diamond[3][j];
                    if (sum == 0)
                    {
                        if (check[i] == 1)
                        {
                            render_diamond[3][i] = 1;
                            break;
                        }
                    }
                }
            }
            if (mouseX >= 260 && mouseX <= 380)
            {
                for (int i = 0; i < 4; i++)
                {
                    int sum = 0;
                    for (int j = 0; j < 4; j++)
                        sum += render_diamond[4][j];
                    if (sum == 0)
                    {
                        if (check[i] == 1)
                        {
                            render_diamond[4][i] = 1;
                            break;
                        }
                    }
                }
            }
            if (mouseX >= 420 && mouseX <= 540)
            {
                for (int i = 0; i < 4; i++)
                {
                    int sum = 0;
                    for (int j = 0; j < 4; j++)
                        sum += render_diamond[5][j];
                    if (sum == 0)
                    {
                        if (check[i] == 1)
                        {
                            render_diamond[5][i] = 1;
                            break;
                        }
                    }
                }
            }
        }
        else
            if (mouseY >= 580 && mouseY <= 700)
            {
                if (mouseX >= 100 && mouseX <= 220)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        int sum = 0;
                        for (int j = 0; j < 4; j++)
                            sum += render_diamond[6][j];
                        if (sum == 0)
                        {
                            if (check[i] == 1)
                            {
                                render_diamond[6][i] = 1;
                                break;
                            }
                        }
                    }
                }
                if (mouseX >= 260 && mouseX <= 380)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        int sum = 0;
                        for (int j = 0; j < 4; j++)
                            sum += render_diamond[7][j];
                        if (sum == 0)
                        {
                            if (check[i] == 1)
                            {
                                render_diamond[7][i] = 1;
                                break;
                            }
                        }
                    }
                }
                if (mouseX >= 420 && mouseX <= 540)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        int sum = 0;
                        for (int j = 0; j < 4; j++)
                            sum += render_diamond[8][j];
                        if (sum == 0)
                        {
                            if (check[i] == 1)
                            {
                                render_diamond[8][i] = 1;
                                break;
                            }
                        }
                    }
                }
            }

    check[0] = 0;
    check[1] = 0;
    check[2] = 0;
    check[3] = 0;

}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}