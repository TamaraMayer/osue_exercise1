/*
   Ryskim graphics module.
   Microtrans Games Inc.

   Author: Cro Magnon, 2019
*/
#include <algorithm>
#include <iostream>

#include "gfx.h"
#include "util.h"

namespace gfx {

static const int screen_width = 1024;
static const int screen_height = 768;


void init() {
   InitWindow(screen_width, screen_height, "Ryskim");
   SetTargetFPS(60);
}

void shutdown() {
   CloseWindow();
}

int window_width() {
   return screen_width;
}

int window_height() {
   return screen_height;
}


static void translate_position(Vector3& position, float x, float y, float z) {
   position.x += x;
   position.y += y;
   position.z += z;
}

//================================ SCENE =====================================
void Scene::draw() {
   unsigned int draws = 0;
   for (auto it : objects) {
      it->draw();

      // ugly hack to get around the raylib MAX_TRIANGLES issue
      if (++draws % 5 == 0) {
         EndMode3D();
         BeginMode3D(camera);
      }
   }
}

void Scene::add_object(Object* object) {
   objects.push_back(object);
}

void Scene::remove_object(Object* object) {
   objects.erase(
      std::remove(objects.begin(), objects.end(), object),
      objects.end());
}

Scene::~Scene() {
   for (auto it : objects) {
      delete it;
   }
}

//================================ ROAD =====================================
Road::Road(float z1, float z2, float width) {
   if (z1 < z2) { 
      util::swap(z1, z2);
   }

   roadblock.color = GRAY;
   roadblock.pos.x = 0.0f;
   roadblock.pos.y = -0.3f; //#roadblock.pos.x - width / 2.0f
   roadblock.pos.z = (z1 + z2) / 2.0f;
   roadblock.size.x = width;
   roadblock.size.y = 0.4f;
   roadblock.size.z = z1 - z2;
}

void Road::translate(float x, float y, float z) {
   translate_position(roadblock.pos, x, y, z);
}

const Vector3& Road::get_position() {
   return roadblock.pos;
}

void Road::draw() {
   DrawCubeV(roadblock.pos, roadblock.size, roadblock.color);
}

//================================ TREE =====================================
Tree::Tree(const Vector3& pos, float height, float width) {
   if (height < width) {
      height = width;
   }
   stem.pos = pos;
   stem.size.x = stem.size.z = width / 4.0f;
   stem.size.y = height - width;
   stem.pos.y += stem.size.y / 2.0f; 
   stem.color = BROWN;

   leaves.pos = pos;
   leaves.pos.y += stem.size.y + width / 2.0f;
   leaves.radius = width / 2.0f;
   leaves.color = GREEN;
}

void Tree::translate(float x, float y, float z) {
   translate_position(stem.pos, x, y, z);
   translate_position(leaves.pos, x, y, z);
}

const Vector3& Tree::get_position() {
   return stem.pos;
}

void Tree::draw() {
   DrawCubeV(stem.pos, stem.size, stem.color);
   DrawSphere(leaves.pos, leaves.radius, leaves.color);
}

//================================ CAR =====================================
Car::Car(const Vector3& pos, float scale, const Color& color) {
   chassis.pos = pos;
   chassis.size.x = 1.0f * scale;
   chassis.size.y = 1.0f * scale;
   chassis.size.z = 2.0f * scale;
   chassis.color = color;

   bounding_box.min = {pos.x - chassis.size.x / 2.0f,
                       pos.y - chassis.size.y / 2.0f,
                       pos.z - chassis.size.z / 2.0f};
   bounding_box.max = {pos.x + chassis.size.x / 2.0f,
                       pos.y + chassis.size.y / 2.0f,
                       pos.z + chassis.size.z / 2.0f};
}

void Car::translate(float x, float y, float z) {
   translate_position(chassis.pos, x, y, z);
   translate_position(bounding_box.min, x, y, z);
   translate_position(bounding_box.max, x, y, z);
}

const Vector3& Car::get_position() {
   return chassis.pos;
}

void Car::draw() {
   DrawCubeV(chassis.pos, chassis.size, chassis.color);
}
}