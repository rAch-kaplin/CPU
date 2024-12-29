#ifdef COLOR
    #define SNPRINTF(buffer, SIZE_BUFFER, COLOR, fmt, ...) snprintf(buffer, SIZE_BUFFER, COLOR fmt COLOR_RESET, ##__VA_ARGS__)
#else
    #define SNPRINTF(buffer, SIZE_BUFFER, COLOR, fmt, ...) snprintf(buffer, SIZE_BUFFER,  fmt, ##__VA_ARGS__)
#endif
