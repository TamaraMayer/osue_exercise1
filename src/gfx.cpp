#include "gfx.h"
#include "util.h"

namespace gfx {

void Scene::draw() {
   for (auto it : objects) {
      it->draw();
   }
}

Scene::~Scene() {
   for (auto it : objects) {
      delete it;
   }
}

Road::Road(float z1, float z2, float width) {
   if (z1 < z2) { 
      util::swap(z1, z2);
   }

   roadblock.color = GRAY;
   roadblock.pos.x = 0.0f;
   roadblock.pos.y = -0.2f; //#roadblock.pos.x - width / 2.0f
   roadblock.pos.z = (z1 - z2) / -2.0f;
   roadblock.size.x = width;
   roadblock.size.y = 0.4f;
   roadblock.size.z = z1 - z2;
}

void Road::draw() {
   DrawCubeV(roadblock.pos, roadblock.size, roadblock.color);
}
}