#include "riscv.h"
#include <string.h>
void init_cpu(CPU *cpu){
    memset(cpu->x, 0, sizeof(cpu->x));
    cpu->pc = 0;
    printf("[INFO] CPU initizlized. ALL registers set to 0.\n");
}
void init_memory(Memory *mem){
    memset(mem->data, 0,sizeof(mem->data));
    printf("[INFO] Memory initialized. Size: %d bytes.\n", MEM_SIZE);
}
void print_registers(CPU *cpu){
    printf("\n========== Register State ========\n");
    for (int i = 0; i < REG_NUM; i++){
        printf("x%-2d = 0x%08x", i,cpu->x[i]);
        if ((i +1 ) % 4 == 0){
            printf("\n");
        } else {
            printf(" ");
        }
    }

    printf("PC = 0x%08x\n", cpu->pc);
    printf("================\n\n");
}
uint32_t fetch(Memory *mem, uint32_t pc){
    if(pc + 3 >=MEM_SIZE) {
        printf("[ERROR] PC out of memory range!\n");
        return 0;
    }
    uint32_t inst = mem ->data[pc] |
                    (mem->data[pc + 1] <<8) |
                    (mem->data[pc + 1] <<16) |
                    (mem->data[pc + 1] <<24);
    return inst;
}
  int instruction_count = 0;
  int branch_taken = 0;
  int function_calls = 0;

  void print_step(int step, const char* description) {
      printf("\n=== Step %d: %s ===\n", step, description);
  }

  void print_cpu_state(CPU *cpu, const char* context) {
      printf("[STATE] %s - PC=0x%x, x1=0x%x, x10=%u, x11=%u\n",
             context, cpu->pc, cpu->x[1], cpu->x[10], cpu->x[11]);
  }

  void print_execution_summary(void) {
      printf("\n=== Execution Summary ===\n");
      printf("Total instructions executed: %d\n", instruction_count);
      printf("Branches taken: %d\n", branch_taken);
      printf("Function calls: %d\n", function_calls);
      printf("========================\n");
  }
