/*
   Ryskim game logic module.
   Microtrans Games Inc.

   Author: Bilbo Bellic, 2019
*/
#include <cstdio>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <thread>

#include "gfx.h"
#include "audio.h"

namespace game {


//==============================  GAME ELEMENTS ===============================

/**
 * Some parameters defining the level
 **/
struct Level {
   float road_len = 300.0f;
   float road_width = 10.0f;
   float tree_dist = 10.0f;
   float enemy_cull_distance = 30.0f;
   double spawn_interval = 0.5f;
};


/**
 * Represents the player character
 **/
class Ryder {
   Vector3 velocity = {0.0f, 0.0f, 0.0f};
   // C. Jarmack: this could be a C++ weak pointer, what happens
   // when the scene graph deletes it and we don't know?
   // we'll access garbage and in the best case crash
   // at least the ownership model is clearly documented in "Scene" - the scene graph
   // cleans up when it shuts down.
   // But when we manually remove elements from the scene graph, we have to be careful 
   // about memory leaks and manually delete the gfx object as well as the game object.
   // I'm not really happy about this solution... I'd rather have the Scene Graph
   // only hold weak pointers without ownership and have this object own the gfx object,
   // so it will be deleted
   // when this game objects dies (and with a C++ weak pointer the scene graph can detect it as well).
   gfx::Object* model; 
   audio::Stream sound;
  public:
   Ryder(const Vector3& pos, float scale, const Color& color) {
      model = new gfx::Car(pos, scale, color);
   }

   void accelerate(float x, float y, float z) {
      velocity.x += x;
      velocity.y += y;
      velocity.z += z;
      // no driving back
      if( velocity.z > 0.0f) {
         velocity.z = 0.0f;
      }
   }

   void update(float time_passed) {
      model->translate(
         velocity.x * time_passed,
         velocity.y * time_passed,
         velocity.z * time_passed);
      velocity.x *= std::pow(0.01f, time_passed);
      velocity.y *= std::pow(0.2f, time_passed);
      velocity.z *= std::pow(0.5f, time_passed);
      sound.play_sine(std::fabs(velocity.z) * 10.0f);
      sound.update();
   }

   const Vector3& get_position() {
      return model->get_position();
   }

   const Vector3& get_velocity() {
      return velocity;
   }

   gfx::Object* get_model() {
      return model;
   }
};


/**
 * Represents enemy vehicles
 **/
class Enemy {
   Vector3 velocity = {0.0f, 0.0f, 0.0f};
   // C. Jarmack: same issue as in "Ryder"
   gfx::Object* model; 
  public:
   Enemy(const Vector3& pos, float scale, const Color& color) {
      model = new gfx::Car(pos, scale, color);
      velocity.z = 1.0f;
   }

   void accelerate(float x, float y, float z) {
      velocity.x += x;
      velocity.y += y;
      velocity.z += z;
   }

   void update(float time_passed) {
      model->translate(
         velocity.x * time_passed,
         velocity.y * time_passed,
         velocity.z * time_passed);
   }

   const Vector3& get_position() {
      return model->get_position();
   }

   gfx::Object* get_model() {
      return model;
   }
};
typedef std::vector<Enemy*> Enemies;


//===============================  GAME FUNCTIONS =============================

/**
 * Initializes the game
 **/
static void init() {
   std::cout << "Initializing graphics subsystem..." << std::endl;
   gfx::init();
   std::cout << "Initializing audio subsystem..." << std::endl;
   audio::init();
}

/**
 * Shuts the game down
 **/
static void shutdown() {
   std::cout << "Shutting down audio subsystem" << std::endl;
   audio::shutdown();
   std::this_thread::sleep_for(std::chrono::milliseconds(200));
   std::cout << "Shuttding down graphics subsystem" << std::endl;
   gfx::shutdown();
}

/**
 * Sets up a default camera view
 **/
static Camera get_default_camera() {
   Camera camera = {0};
   camera.position.x = 0.0f;
   camera.position.y = 15.0f;
   camera.position.z = 10.0f;
   camera.target = {0.0f, 0.0f, 0.0f};
   camera.up = {0.0f, 1.0f, 0.0f};
   camera.fovy = 45.0f;
   camera.type = CAMERA_PERSPECTIVE;

   return camera;
}

/**
 * Generate trees along the road
 **/
static void generate_trees(gfx::Scene& scene, const Level& level) {
   std::default_random_engine generator;
   std::normal_distribution<float> height_distribution(5.0f, 0.01f);
   std::normal_distribution<float> width_distribution(3.0f, 0.2f);
   auto tree_dist = level.road_width / 2.0f + 1.0f;
   int tree_num = 0;

   for (float posz = 0.0f; posz >= -level.road_len; posz -= level.tree_dist) {
      Vector3 treepos_left = {-tree_dist, 0.0f, posz};
      auto tree_left = new gfx::Tree(treepos_left,
                              height_distribution(generator),
                              width_distribution(generator));
      scene.add_object(tree_left);
      Vector3 treepos_right = {tree_dist, 0.0f, posz};
      auto tree_right = new gfx::Tree(treepos_right,
                              height_distribution(generator),
                              width_distribution(generator));
      scene.add_object(tree_right);
      tree_num += 2;
   }
   std::cout << "Planting " << tree_num << " trees." << std::endl;
}

/**
 * Spawn an enemy with random properties in front of the player
 **/
static void spawn_random_enemy(Enemies& enemies, Ryder& player, gfx::Scene& scene, Level& level) {
   static std::default_random_engine generator;
   static std::uniform_int_distribution<unsigned int> color_distribution(50, 200);
   static std::normal_distribution<float> scale_distribution(1.0f, 0.1f);
   static std::normal_distribution<float> speed_distribution(23.0f, 0.5f);
   float scale = scale_distribution(generator);
   std::uniform_real_distribution<float> x_distribution(
                        -(level.road_width - scale) / 2.0f,
                        (level.road_width - scale) / 2.0f);
   Color color = {static_cast<unsigned char>(color_distribution(generator)),
                  static_cast<unsigned char>(color_distribution(generator)),
                  255,
                  255};
   Vector3 position = {x_distribution(generator),
                       0.5f,
                       player.get_position().z - 90.0f};
   Enemy* enemy = new Enemy(position, scale, color);
   enemy->accelerate(0.0f, 0.0f, speed_distribution(generator));
   enemies.push_back(enemy);
   scene.add_object(enemy->get_model()); 
}


/**
 * Main game loop
 **/
void game_loop() {
   // generate level and renderer scene
   Level level;
   gfx::Scene scene(get_default_camera());
   float cam_distance = 10.0f;

   // build the road
   // C. Jarmack - make this a unique_ptr?
   auto road = new gfx::Road(30.0f, -level.road_len, level.road_width);
   scene.add_object(road);

   // plant a couple trees for visual pleasure
   generate_trees(scene, level);

   // green grass
   Color ground_color = { 0, 117, 44, 255 }; 

   // the player
   Vector3 playerPosition = {0.0f, 0.5f, 2.0f};
   Ryder ryder(playerPosition, 1.0f, RED);
   scene.add_object(ryder.get_model());

   // enemies
   Enemies enemies;
   double last_spawn = GetTime();

   bool collision = false;

   while (!WindowShouldClose()) {
      // input handling
      if (IsKeyDown(KEY_RIGHT))
         ryder.accelerate(1.0f, 0.0f, 0.0f);
      if (IsKeyDown(KEY_LEFT))
         ryder.accelerate(-1.0f, 0.0f, 0.0f);
      if (IsKeyDown(KEY_DOWN))
         ryder.accelerate(0.0f, 0.0f, 1.0f);
      if (IsKeyDown(KEY_UP))
         ryder.accelerate(0.0f, 0.0f, -1.0f);
      ryder.update(GetFrameTime());

      // ran out of road? create a new one
      if (ryder.get_position().z < road->get_position().z) {
         auto road_begin = ryder.get_position().z + 30.0f;
         road = new gfx::Road(road_begin,
                              road_begin - level.road_len,
                              level.road_width);
         scene.add_object(road); 
      }

      // update follow cam
      scene.get_camera().position.z = ryder.get_position().z + cam_distance;
      scene.get_camera().target.z = ryder.get_position().z - 7.0f - 0.1f * std::fabs(ryder.get_velocity().z);

      // spawn new enemies
      if (GetTime() - last_spawn > level.spawn_interval) {
         last_spawn = GetTime();
         spawn_random_enemy(enemies, ryder, scene, level);
      }

      // update existing enemies
      for (auto it = std::begin(enemies);
                it != std::end(enemies);) {

         auto enemy = *it;
         enemy->update(GetFrameTime());

         // if enemy far away from us, remove them
         if (enemy->get_position().z - ryder.get_position().z > level.enemy_cull_distance) {
            // remove the gfx object (model) from the gfx scene
            scene.remove_object(enemy->get_model());
            // remove the game oject from the enemies list
            it = enemies.erase(it);
            delete enemy;
         }
         else {
            ++it;
         }

         // check collisions of player with this enemy
         if (CheckCollisionBoxes(ryder.get_model()->get_bounding_box(),
                                enemy->get_model()->get_bounding_box())) {
            //enemy->get_model()->translate(0.0f, 0.0f, -1.0f);
            BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(scene.get_camera());
            scene.draw();
            EndMode3D();
            DrawText("FAIL", gfx::window_width() / 2 - 100, gfx::window_height() / 2, 70, RED);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            return;
         }
      }

      // Draw
      BeginDrawing();
      ClearBackground(ground_color);
      BeginMode3D(scene.get_camera());
      scene.draw();
      //DrawGrid(100, 1.0f); // Draw a grid
      EndMode3D();
      DrawFPS(10, 10);
      EndDrawing();
   }
}

/**
 * Run the game 
 **/
void run() {
   init();
   game_loop();
   shutdown();
}

} // namespace game