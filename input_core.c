#include <stdint.h>

char* keymap[] = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
int v_row = 1;
int v_col = 0;
int s_row = 1;
int s_col = 0;

void find_char(char c) {
    for(int r=0; r<3; r++) {
        for(int c_idx=0; c_idx<11; c_idx++) {
            if(keymap[r][c_idx] == c) {
                v_row = r;
                v_col = c_idx;
                return;
            }
        }
    }
}

char process_alien_key(char mod, char target) {
    switch(mod) {
        case '&': v_col++; break;
        case '+': if(v_col>0) v_col--; break;
        case '*': if(v_row>0) v_row--; break;
        case 'l': if(v_row<2) v_row++; break;
    }
    
    if(v_col >= (int)strlen(keymap[v_row])) v_col = strlen(keymap[v_row])-1;
    
    return keymap[v_row][v_col];
}

void handle_spawn_command(char* cmd_str) {
    char target = 0;
    for(int i=0; cmd_str[i]!=0; i++) {
        if(cmd_str[i]=='{' && cmd_str[i+1]=='[') {
            target = cmd_str[i+2];
            break;
        }
    }

    if(target != 0) {
        find_char(target);
        s_row = v_row;
        s_col = v_col;
        kprint("\nADL0- :: Spawn Anchored at [");
        put_char(target);
        kprint("]\n");
    }
}
