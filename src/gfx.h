#include "raylib.h"
#include <vector>

namespace gfx {

class Object {
 public:
   Object() {}
   virtual void draw() = 0;
   virtual ~Object() {}
};

class Scene {
   Camera camera;
   std::vector<Object *> objects;

 public:
   Scene(Camera cam) : camera(cam) {}
   void draw();
   inline Camera& get_camera() { return camera; }
   ~Scene();
};

struct Line {
   Vector3 start;
   Vector3 end;
   Color color;
};

struct Cube {
   Vector3 pos;
   Vector3 size;
   Color color;
};

class Road : public Object {
   Cube roadblock;
 public:
   Road(float z1, float z2, float width);
   void draw() override;
};

} // namespace gfx