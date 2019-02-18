namespace drm {
typedef unsigned int code_id;

code_id get_random_code_id();

/*
   Returns a user query for a given code_id.
   \param id the id for which to retrieve a query string
   \param result_query the resulting query will be written here
   \return 0 if successful
*/
int const get_query(code_id id, char* result_query);

/*
   Returns a user query for a given code_id.
   \param id the id for which to retrieve a query string
   \param result_query the resulting query will be written here
   \return 0 if successful
*/
int const get_code(code_id id, char* result_code);

/*
  Checks a user entered code against the real code.
  \param id the id of the real code.
  \param user_code the code the user entered.
  \return true if the user entered the correct code, otherwise false.

  (A.Typical) TODO: in future versions, user_code can be set to NULL
  to repeat a check with a stored version of the user_code.
  This is not implemented yet.
*/
bool check_code(code_id id, const char* user_code);
}
