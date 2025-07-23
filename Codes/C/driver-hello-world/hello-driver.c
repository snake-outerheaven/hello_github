#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void){
  printk(KERN_INFO "Hello world\n");
  /*
   * um valor que nao retorna 0 indica que o driver falhou
   */

   return 0;
}


void cleanup_module(void){
  printk(KERN_INFO "Goodbye World!\n");
}


// simples driver que diz hello world 
