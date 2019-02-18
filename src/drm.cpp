/*
   Digital Rights Management (DRM) module.
   Microtrans Games Inc.

   Author: Ada Typical, 2019
*/
#include "drm.h"

#include <cstring> 

namespace drm {

// (A.Typical) for now we store the codes here, should move them to a safer place in future
static code_id MAX_CODES = 3;
static const char* codes[] = {"ground", "fork", "powerup"};
static const char* queries[] = {"Please enter the second word on page 5 in your handbook."
                                , "Please enter the 10th word on page 10 in your handbook."
                                , "Please enter the 7th word on page 3 in your handbook."};

code_id get_random_code_id() {
   return 0;
}

/*
  (A.Typical) TODO: this will retrieve the query string from somewhere else,
  consider this implementation temporary
*/
int const get_query(code_id id, char* result_query) {
   if (id < MAX_CODES) {
      strcpy(result_query, queries[id]);
      return 0;
   }
   return -1;
}

/*
  (A.Typical) TODO: this will retrieve the query string from somewhere else,
  consider this implementation temporary
*/
int const get_code(code_id id, char* result_code) {
   if (id < MAX_CODES) {
      strcpy(result_code, codes[id]);
      return 0;
   }
   return -1;
}

bool check_code(code_id id, const char* user_code) {
   static char tmp_user_code[8];
   static char tmp_real_code[8];
   
   if (get_code(id, tmp_real_code) != 0) {
      return false;
   }

   // (A.Typical) we copy the user code because in future version
   // we would like to store it for future checks in case some
   // cracker somehow skips the initial code check
   strcpy(tmp_user_code, user_code);

   if (!strcmp(tmp_real_code, tmp_user_code)) {
      return true;
   }
   return false;
}

}