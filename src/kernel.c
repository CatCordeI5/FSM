#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void kprint(const char* str) {
    volatile uint16_t* vga = (uint16_t*)0xB8000;
    int i = 0;
    while (str[i] != 0) {
        vga[i] = (0x0F << 8) | str[i];
        i++;
    }
}

char get_key() {
    while (!(inb(0x64) & 0x01)); 
    return inb(0x60);
}

char scan_to_ascii(uint8_t sc) {
    static const char map[] = {0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h',
    'j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0};
    return (sc < 58) ? map[sc] : 0;
}

void _start() {
    kprint("FSM: FUCK SYSTEM-LIKE INITIALIZED\n");
    kprint("~-{[LadG]}~ ");
    
    char buffer[256];
    int idx = 0;
    
    while(1) {
        char c = scan_to_ascii(get_key());
        if (c == 0) continue;
        
        if (c == '\n') {
            buffer[idx] = 0;
            kprint("\n");

            if (idx > 9 && buffer[0]=='~' && buffer[1]=='o' && buffer[3]=='c' && buffer[7]=='~') {
                char* cmd = &buffer[9];
                if (cmd[0]=='h' && cmd[1]=='e' && cmd[2]=='l' && cmd[3]=='p' && cmd[4]==0) {
                    kprint("PROTOCOLS:\n~o com ~ wifi\n~o com ~ shifthat\n");
                } else if (cmd[0]=='w' && cmd[1]=='i' && cmd[2]=='f' && cmd[3]=='i' && cmd[4]==0) {
                    kprint("~-{[LadG]}~ Scanning Raw Spectrum...\n");
                } else {
                    kprint("ERROR: Unknown Syntax.\n");
                }
            } else {
                kprint("ERROR: Invalid Protocol. Use '~o com ~ [cmd]'\n");
            }
            
            kprint("~-{[LadG]}~ ");
            idx = 0;
        } else if (c == '\b') {
            if (idx > 0) {
                idx--;
                volatile uint16_t* vga = (uint16_t*)0xB8000;
                vga[20 + idx] = (0x0F << 8) | ' '; 
            }
        } else {
            buffer[idx++] = c;
            volatile uint16_t* vga = (uint16_t*)0xB8000;
            vga[20 + idx - 1] = (0x0F << 8) | c;
        }
    }
}
