[bits 16]
[org 0x7c00]

section .text

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Load kernel from sector 2 to 0x10000
    mov bx, 0x1000
    mov es, bx
    xor bx, bx
    mov ah, 0x02
    mov al, 20
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    int 0x13

    jc hang
    jmp 0x1000:0x0000

hang:
    hlt
    jmp hang

times 510-($-$$) db 0
dw 0xaa55
