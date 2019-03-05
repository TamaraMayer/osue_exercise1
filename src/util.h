#ifndef RYSKIM_UTIL
#define RYSKIM_UTIL

namespace util {
   template<typename T> void swap(T& a, T& b) {
      T tmp = a;
      a = b;
      b = tmp;       
   }
}

#endif