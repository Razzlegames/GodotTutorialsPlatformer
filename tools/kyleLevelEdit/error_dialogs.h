/* vim: set filetype=cpp.doxygen : */
#ifndef ERROR_DIALOGS_H
#define ERROR_DIALOGS_H 

void error_dialog(const char* str);


#define  ERROR_DIALOG(fmt, ...) { char temp2[0xFFF];\
  snprintf(temp2, 0xFFF, "ERROR: " fmt, ##__VA_ARGS__ ); \
  error_dialog( temp2); }

#define ERROR(fmt, ...)\
  ERROR_DIALOG(fmt, ##__VA_ARGS__); \
  fprintf(stderr, "ERROR: " fmt, ##__VA_ARGS__);

#endif /* ERROR_DIALOGS_H */
