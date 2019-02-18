#include <iostream>

#include "drm.h"

int main(int argc, char* argv[]) {

   // (C.Jarmack) the DRM API is awful as it doesn't tell us the maximum string size
   // for its get_query and get_code calls... we have to do something about this.
   // could we PLEASE use C++ strings in future?
   // consider this an ugly hack for now.
   char query[255];
   std::string user_code;

   // perform DRM check
   drm::code_id code_id = drm::get_random_code_id();
   drm::get_query(code_id, query);

   std::cout << "Ryskim DRM v0.2.2" << std::endl;
   std::cout << query << std::endl;
   std::cin >> user_code;
   
   if(!drm::check_code(code_id, user_code.c_str()) {
       std::cerr << "Invalid code, quitting!" << std::endl;
       return -1;
   }
   return 0;
}