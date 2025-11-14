const char msg[] = "Hello, World!\n";

void _start(void) {
    // write(1, msg, sizeof(msg)-1)
    asm volatile (
        "mov $1, %%rax\n"      // sys_write
        "mov $1, %%rdi\n"      // fd = stdout
        "mov %0, %%rsi\n"      // buf
        "mov %1, %%rdx\n"      // len
        "syscall\n"
        :
        : "r"(msg), "r"(sizeof(msg)-1)
        : "rax","rdi","rsi","rdx","rcx","r11","memory"
    );

    // _exit(0)
    asm volatile (
        "mov $60, %%rax\n"     // sys_exit
        "xor %%rdi, %%rdi\n"   // status 0
        "syscall\n"
        :
        :
        : "rax","rdi","rcx","r11","memory"
    );
}
