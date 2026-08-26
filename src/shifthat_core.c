#include <stdint.h>

typedef struct {
    uint32_t pid;
    char name[16];
    int threat_level;
} process_info_t;

process_info_t monitored_procs[100];
int is_active = 0;

void shifthat_init() {
    kprint("[SHIFTHAT] Core defense initialized.\n");
    is_active = 1;
}

void shifthat_scan() {
    if(!is_active) return;
    
    for(int i=0; i<100; i++) {
        if(monitored_procs[i].threat_level > 80) {
            kprint("[SHIFTHAT] PURGING THREAT: ");
            kprint(monitored_procs[i].name);
            kprint("\n");
            monitored_procs[i].threat_level = 0;
        }
    }
}
