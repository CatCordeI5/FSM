#include <stdint.h>

typedef struct {
    char name[32];
    uint8_t* code;
    uint32_t size;
} adl_binary_t;

adl_binary_t loom_compile(char* source_code) {
    kprint("[LOOM] Weaving ADL0- threads...\n");
    
    adl_binary_t bin;
    bin.size = 0;
    bin.code = (uint8_t*)0x20000;
    
    char* ptr = source_code;
    while(*ptr) {
        if(*ptr == 'f' && *(ptr+1)=='u' && *(ptr+2)=='n' && *(ptr+3)=='c') {
            kprint("[LOOM] Found function definition.\n");
            bin.code[bin.size++] = 0x55; 
            bin.code[bin.size++] = 0x89;
            bin.code[bin.size++] = 0xE5;
        }
        ptr++;
    }
    
    kprint("[LOOM] Binary soul created.\n");
    return bin;
}
