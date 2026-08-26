#include <stdint.h>

void _start() {
    kprint("FSM: FUCK SYSTEM-LIKE INITIALIZED\n");
    shifthat_init();
    
    while(1) {
        shifthat_scan();
        
        char mod = get_key_raw();
        if(mod == '~') {
            char cmd_buffer[100];
            read_command(cmd_buffer);
            
            if(strstr(cmd_buffer, "set spawn point")) {
                handle_spawn_command(cmd_buffer);
            } else if (strstr(cmd_buffer, "loom")) {
                loom_compile(load_file_from_disk(cmd_buffer));
            }
        } else {
            char target = get_key_raw();
            char result = process_alien_key(mod, target);
            put_char(result);
        }
    }
}
