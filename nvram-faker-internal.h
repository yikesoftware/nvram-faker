#ifndef __nvram_faker_internal_h
#define __nvram_faker_internal_h

#ifndef NVRAM_EXE
void initialize_dict(void) __attribute__((constructor));
void end(void) __attribute__((destructor));
#else
void initialize_dict(void);
void end(void);
#endif

#define DICT_FILE_PATH "./nvram.dict"

#ifdef DEBUG
#define DEBUG_PRINTF(format,...) fprintf(stderr,format,## __VA_ARGS__)
#else
#define DEBUG_PRINTF(format,...)
#endif

#define LOG_PRINTF(format,...) fprintf(stderr,format, ## __VA_ARGS__)

#endif /* __nvram_faker_internal_h */
