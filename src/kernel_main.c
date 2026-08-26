#include <stdint.h>

extern void kprint(const char* str);
extern void put_char(char c);
extern char get_key_raw();
extern void shifthat_init();
extern void shifthat_scan();
extern adl_binary_t loom_compile(char* source_code);
extern void handle_spawn_command(char* cmd_str);
extern char process_alien_key(char mod, char target);

void kprint(const char* str) {
    volatile uint16_t* vga = (uint16_t*)0xB8000;
    int i = 0;
    while (str[i] != '\0') {
        vga[i] = (0x0F << 8) | str[i];
        i++;
    }
}

void put_char(char c) {
    volatile uint16_t* vga = (uint16_t*)0xB8000;
    static int cursor = 0;
    vga[cursor++] = (0x0F << 8) | c;
}

char get_key_raw() {
    return 0; 
}

void _start() {
    kprint("FSM: FUCK SYSTEM-LIKE INITIALIZED\n");
    shifthat_init();
    
    while(1) {
        shifthat_scan();
        
        char mod = get_key_raw();
        if(mod == '~') {
            kprint("\n[COMMAND MODE]\n");
        } else {
            char target = get_key_raw();
            char result = process_alien_key(mod, target);
            put_char(result);
        }
    }
}
