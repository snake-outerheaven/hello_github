org 0x7C00
bits 16

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov si, msg

.print:
    lodsb
    cmp al, 0
    je .hang
    mov ah, 0x0E
    mov bh, 0
    mov bl, 7
    int 0x10
    jmp .print

.hang:
    hlt
    jmp .hang

msg db "Oi Mundo!", 0

times 510-($-$$) db 0
dw 0xAA55
