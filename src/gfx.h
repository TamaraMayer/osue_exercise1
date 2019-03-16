/*
   Ryskim graphics module.
   Microtrans Games Inc.

   Author: Cro Magnon, 2019
*/
#ifndef RYSKIM_GFX
#define RYSKIM_GFX

#include "raylib.h"
#include <vector>

namespace gfx {


void init();
void shutdown();
int window_width();
int window_height();

/**
 * Represents a graphical object in a scene
 **/
class Object {
 protected:
   BoundingBox bounding_box;
 public:
   Object() {}
   virtual void draw() = 0;
   virtual void translate(float x, float y, float z) = 0;
   virtual const Vector3& get_position() = 0;
   virtual const BoundingBox& get_bounding_box() { return bounding_box; }
   virtual ~Object() {}
};


/**
 * Represents a scene with Camera and graphical objects
 **/
class Scene {
   Camera camera;
   std::vector<Object *> objects;

 public:
   Scene(const Camera& cam) : camera(cam) {}
   void draw();

   /**
    * Adds an object to the scene and takes ownership (will be deleted by the scene graph).
    * \param object the Object to add.
    **/
   void add_object(Object* object);
   void remove_object(Object* object);
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


struct Sphere {
   Vector3 pos;
   float radius;
   Color color;
};


class Road : public Object {
   Cube roadblock;
 public:
   Road(float z1, float z2, float width);
   virtual void translate(float x, float y, float z) override;
   virtual const Vector3& get_position() override;
   virtual void draw() override;
};

class Tree : public Object {
   Cube stem;
   Sphere leaves;
 public:
   /**
    * Constructor
    * \param pos position of the bottom and center of the tree stem.
    * \param height height of the tree.
    * \param width maximum width of the tree.
    **/
   Tree(const Vector3& pos, float height, float width);
   void translate(float x, float y, float z) override;
   virtual const Vector3& get_position() override;
   void draw() override;
};


class Car : public Object {
   Cube chassis;
 public:
   Car(const Vector3& pos, float scale, const Color& color);
   void translate(float x, float y, float z) override;
   virtual const Vector3& get_position() override;
   void draw() override;
};
} // namespace gfx

#endif