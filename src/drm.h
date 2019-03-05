#ifndef RYSKIM_DRM
#define RYSKIM_DRM

namespace drm {
typedef unsigned int code_id;

/*
  Returns a random DRM code_id.
  \return a code_id to be used with get_query/get_code.
*/
code_id get_random_code_id();

/*
   Returns a user query for a given code_id.
   \param id the id for which to retrieve a query string
   \param result_query the resulting query will be written here
   \return 0 if successful
*/
int get_query(code_id id, char* result_query);

/*
   Returns a user query for a given code_id.
   \param id the id for which to retrieve a query string
   \param result_query the resulting query will be written here
   \return 0 if successful
*/
int get_code(code_id id, char* result_code);

/*
  Checks a user entered code against the real code.
  \param id the id of the real code.
  \param user_code the code the user entered, uses cached version if set to nullptr.
  \return true if the user entered the correct code, otherwise false.
*/
bool check_code(code_id id, const char* user_code);
}

#endif