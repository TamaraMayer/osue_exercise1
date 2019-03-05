#include "gfx.h"

namespace game
{
#define MAX_FONTS 8

void init() {
   int screenWidth = 1024;
   int screenHeight = 768;

   InitWindow(screenWidth, screenHeight, "Ryskim");
   SetTargetFPS(60);
}


void shutdown() {
   CloseWindow();
}

Camera get_default_camera() {
   // Define the camera to look into our 3d world
   Camera camera = {0};
   camera.position = (Vector3){0.0f, 15.0f, 10.0f};
   camera.target = (Vector3){0.0f, 0.0f, 0.0f};
   camera.up = (Vector3){0.0f, 1.0f, 0.0f};
   camera.fovy = 45.0f;
   camera.type = CAMERA_PERSPECTIVE;

   return camera;
}

void run() {
   init();

   gfx::Scene scene(get_default_camera());
   gfx::Road road(10.0f, -50.0f, 10.0f);
   float cam_distance = 15.0f;

   Vector3 playerPosition = {0.0f, 0.5f, 2.0f};
   Vector3 playerSize = {1.0f, 1.0f, 2.0f};
   Color playerColor = GREEN;

   Vector3 enemyBoxPos = {-4.0f, 4.0f, -15.0f};
   Vector3 enemyBoxSize = {2.0f, 2.0f, 2.0f};

   Vector3 enemySpherePos = {4.0f, 0.0f, -30.0f};
   float enemySphereSize = 1.5f;

   bool collision = false;

   while (!WindowShouldClose()) {
      // Update
      //----------------------------------------------------------------------------------

      // Move player
      if (IsKeyDown(KEY_RIGHT))
         playerPosition.x += 0.2f;
      if (IsKeyDown(KEY_LEFT))
         playerPosition.x -= 0.2f;
      if (IsKeyDown(KEY_DOWN))
         playerPosition.z += 0.2f;
      if (IsKeyDown(KEY_UP))
         playerPosition.z -= 0.2f;

      scene.get_camera().position.z = playerPosition.z + cam_distance;
      scene.get_camera().target.z = playerPosition.z;
      collision = false;

      // Check collisions player vs enemy-box
      if (CheckCollisionBoxes(
              (BoundingBox){(Vector3){playerPosition.x - playerSize.x / 2,
                                      playerPosition.y - playerSize.y / 2,
                                      playerPosition.z - playerSize.z / 2},
                            (Vector3){playerPosition.x + playerSize.x / 2,
                                      playerPosition.y + playerSize.y / 2,
                                      playerPosition.z + playerSize.z / 2}},
              (BoundingBox){(Vector3){enemyBoxPos.x - enemyBoxSize.x / 2,
                                      enemyBoxPos.y - enemyBoxSize.y / 2,
                                      enemyBoxPos.z - enemyBoxSize.z / 2},
                            (Vector3){enemyBoxPos.x + enemyBoxSize.x / 2,
                                      enemyBoxPos.y + enemyBoxSize.y / 2,
                                      enemyBoxPos.z + enemyBoxSize.z / 2}}))
         collision = true;

      // Check collisions player vs enemy-sphere
      if (CheckCollisionBoxSphere(
              (BoundingBox){(Vector3){playerPosition.x - playerSize.x / 2,
                                      playerPosition.y - playerSize.y / 2,
                                      playerPosition.z - playerSize.z / 2},
                            (Vector3){playerPosition.x + playerSize.x / 2,
                                      playerPosition.y + playerSize.y / 2,
                                      playerPosition.z + playerSize.z / 2}},
              enemySpherePos, enemySphereSize))
         collision = true;

      if (collision)
         playerColor = RED;
      else
         playerColor = GREEN;
      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(RAYWHITE);

      BeginMode3D(scene.get_camera());

      road.draw();

      // Draw enemy-box
      DrawCube(enemyBoxPos, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, GRAY);
      DrawCubeWires(enemyBoxPos, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, DARKGRAY);

      // Draw enemy-sphere
      DrawSphere(enemySpherePos, enemySphereSize, GRAY);
      DrawSphereWires(enemySpherePos, enemySphereSize, 16, 16, DARKGRAY);

      // Draw player
      DrawCubeV(playerPosition, playerSize, playerColor);




      //DrawGrid(10, 1.0f); // Draw a grid

      EndMode3D();

      DrawText("Move player with cursors to collide", 220, 40, 20, GRAY);

      DrawFPS(10, 10);

      EndDrawing();
   }

   shutdown();
}

} // namespace game