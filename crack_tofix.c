/**
 * (c) Dorian Dactic 2019
 * Written during my internship at Microtrans games
 * I tried to document everything I've learnt in the comments.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// D. Dactic: this is a function declaration
// necessary if we want to use this function before
// the definition. The definition is at the bottom of this file.
// Often you find declarations in header files in the implementations
// in c/cpp files.
void scan(char* buffer, long buflen);

int main(int argc, char* argv[]) {
   // D. Dactic: I give up, I copied all this stuff from stackoverflow
   // but I can't get it to work :(
   // I think I'll quit this job...
   long fsize = 0; // size of the binary
   char* buffer = NULL; // here we'll hold the data from the binary
   size_t result = 0;

   // the user has to supply the path to the binary
   if (argc < 2) {
      printf("Usage: crack ryskim.exe\n");
      return -1;
   }

   // D. Dactic: this opens the file in binary mode
   const char* exectuable_path = argv[1];
   FILE* fp = fopen(exectuable_path, "rb");
   if (fp == NULL) {
      printf("Can not read %s\n", exectuable_path);
      return -2;
   }

   // D. Dactic: obtain file size
   // supposedly this shall jump to the end of the file
   // tell us the current position and then rewind
   // perhaps I messed this up?
   fseek (fp /* TOFIX */ );
   fsize = /* TOFIX */; 
   rewind (fp);

   // allocate memory to contain the whole file
   // we have to keep the buffer size in another variable (fsize)
   // otherwise we don't know if we're already out of bounds
   // C++ containers like std::vector or std::array typically wrap this
   // for us and provide a "size" member function
   // TOFIX
   buffer = malloc; // TOFIX 
   if (buffer == NULL) {
      printf ("Could not allocate memory"); 
      return -3;
   }

   // read the file now into buffer 
   result = fread /* TOFIX */; 
   if (result != fsize) {
      printf ("Error reading binary");
      return -4;
   }
  
   // so we can close our file
   fclose (fp);

   scan(buffer, fsize);

   // free memory before leaving
   // TOFIX free
   return 0;
}

/** 
 * Scans the ryksim binry for strings interesting regarding DRM
 **/
void scan(char* buffer, long buflen) {
   const char* findstr = "Please";
   const int findstr_len = 6;
   const int preview_window = 200;
   char* pos = buffer;

   // pointer arithmetic 101
   // let's print the address buffer is pointing to
   // %x formats as hex
   printf("Debug information\n");
   printf("-----------------\n");
   printf("Size of buffer: %lu\n", sizeof(buffer)); 
   printf("Size of *buffer: %lu\n", sizeof(*buffer)); 

   // pointer contains address of target as value
   printf("Address of buffer: %p\n", buffer);

   // get the value at the first (0th) position
   printf("Element in buffer[0]: %x\n", buffer[0]);

   // get the address of the value at the first position using &
   printf("Address of buffer[0]: %p\n", &buffer[0]);

   // dereference the pointer with * to get the value at the first position
   printf("Element in buffer[0]: %x\n", *buffer);

   // increment the address by one element (of size buffer)
   // then dereference the pointer to get the value
   printf("Element in buffer[1]: %x\n", *(buffer+1));

   // buffer[i] == *(buffer + i)
   printf("Element in buffer[1]: %x\n", buffer[1]);

   printf("\nScanning for 'Please'\n");
   printf("---------------------\n");

   // so now increment our pointer to navigate through the buffer
   int preview_num = 0;
   while (pos < /* TOFIX */) {
      if (*pos == 'P') {
         // check if findstr is at pos
         if (memcmp /* TOFIX */) {
            //printf ("\nFound: %s", pos);
            printf("\n%p: ", pos);
            preview_num = preview_window;
         }
      }
      if (preview_num > 0) {
         // a string ends here (potentially)
         if(*pos == 0) {
            printf("\n%p: ", pos);
         }
         // otherwise interpret as character
         else {
            printf("%c", *pos);
         }
         --preview_num;
      }

      /* TOFIX set pos to next memory address */
   }
   printf("\n\nDone\n");
}