#include <iostream>
#include <string>

#include "drm.h"
#include "game.h"

bool drm_check() {
   return true;
   // (C.Jarmack) the DRM API is awful as it doesn't tell us the maximum string size
   // for its get_query and get_code calls... we have to do something about this.
   // could we PLEASE use C++ strings in future?
   // consider this an ugly hack for now.
   char query[255];
   int tries = 0;
   const int max_tries = 3;
   std::string user_code;

   drm::code_id code_id = drm::get_random_code_id();
   drm::get_query(code_id, query);

   std::cout << "Ryskim DRM v0.2.2" << std::endl;
   std::cout << query << std::endl;
   std::cin >> user_code;

   while(!drm::check_code(code_id, user_code.c_str())) {
       if (++tries >= max_tries) {
           std::cerr << "Invalid code, quitting!" << std::endl;
           return false;
       }
       std::cout << "Invalid code, try again!" << std::endl;
       std::cin >> user_code;
   }
   return true;
}

int main(int argc, char* argv[]) {
   if (!drm_check()) {
       return -1;
   }
   std::cout << "Welcome to Ryskim! Loading..." << std::endl;
   game::run();
   return 0;
}