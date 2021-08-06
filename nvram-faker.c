#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nvram-faker.h"
//include before ini.h to override ini.h defaults
#include "nvram-faker-internal.h"
#include "dictionary.h"

#define RED_ON "\033[22;31m"
#define RED_OFF "\033[22;00m"
#define DIC_LINE_BUF 1024*1024               

dictionary *glo_nvram=NULL;

char *fetch_line(char *buf, int size, FILE *stream) {
    char *cursor = buf;                                   
    char *ret;                                              
    memset(buf, 0, size);                                 
    ret = fgets(buf, size, stream);                   
    if(ret){                                                
        while(*cursor != '\0' && (cursor-buf) < size){  
            if(*cursor == '\n' || *cursor == '\r'){         
                *cursor = '\0';                             
            }
            cursor++;                                               
        }                                                   
    }                                                       
    return ret;                                                    
}

void initialize_dict(void)
{
    char line_buf[DIC_LINE_BUF] = {0};

    glo_nvram = dictionary_new(0);
    
    FILE *nvm_file_fp = fopen(DICT_FILE_PATH, "rw");
    DEBUG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF"DICT_FILE_FP: %p\n", nvm_file_fp);

    if(!nvm_file_fp) return;

    while(fetch_line(line_buf, DIC_LINE_BUF, nvm_file_fp)){
        char *key = line_buf;
        char *value = NULL;
        //DEBUG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" line_buf: %s\n", line_buf);
        char *sep = strchr(line_buf, '=');
        if(sep){
            *sep = '\0';
            value = sep+1;
        } else{
            continue;
        }        
        char *ptr = strdup(value);
        dictionary_set(glo_nvram, key, (void *)ptr);
        DEBUG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" kv: %s=%s\n", key, ptr);
    }
    DEBUG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" Test get: %s\n", nvram_get("oauth_dm_refresh_ticket"));
    fclose(nvm_file_fp);
}

void end(void)
{
    dictionary_del(glo_nvram);
}

char *nvram_get(const char *key)
{
    LOG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" nvram_get: %s\n", key);
    char *value = dictionary_get(glo_nvram, key, NULL);
    if(!value){
        LOG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" got: %s=NULL\n", key);
    } else{
        LOG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" got: %s=%s\n", key, value);   
    }
    return value;
}

int nvram_get_int(const char *key){
    char *value;
    value = nvram_get(key);
    if(!value){
        return ~0;
    } else{
        return atoi(value);
    }
}

int nvram_set(const char *key, const char *value)
{
    int ret;
    if(!key || !value){
        return ~0;
    }
    LOG_PRINTF(RED_ON"[FAKE NVRAM]"RED_OFF" nvram_set: %s=%s\n", key, value);
    ret = dictionary_set(glo_nvram, key, strdup(value));
    return ret;
}

int nvram_set_int(const char *key, int value){
    char int_val[32] = {0};
    int ret;

    if(!key || !value){
        return ~0;
    }
    snprintf(int_val, 31, "%d", value);
    ret = nvram_set(key, int_val);
    return ret;
}

