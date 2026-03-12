#include "riscv.h"
void execute_add(CPU *cpu, R_Type *r){
    if (r->rd == 0) return;

    cpu->x[r->rd] = cpu->x[r->rs1] + cpu->x[r->rs2];
    printf("[EXEC] ADD: x%d =x%d + x%d = %u\n",
            r->rd, r->rs1, r->rs2, cpu->x[r->rd]);
}
void execute_sub(CPU *cpu, R_Type *r){
    if (r->rd == 0) return;

       cpu->x[r->rd] = cpu->x[r->rs1] - cpu->x[r->rs2];
       printf("[EXEC] SUB: x%d = x%d - x%d = %u\n",
               r->rd, r->rs1, r->rs2, cpu->x[r->rd]);
}
void execute_addi(CPU *cpu, I_Type *i){
    if(i->rd == 0) return;

    cpu->x[i->rd] = cpu->x[i->rs1]  + i->imm;
    printf("[EXEC] ADDI: x%d =x%d + %d = %u\n",
             i->rd, i->rs1, i->imm, cpu->x[i->rd]);
}
void execute_and(CPU *cpu, R_Type *r){
     if (r->rd == 0) return;

     cpu->x[r->rd] = cpu->x[r->rs1] & cpu ->x[r->rs2];
     printf("[EXEC] AND: x%d = x%d & x%d = 0x%08x & 0x%08x = 0x%08x\n",
             r->rd, r->rs1, r->rs2,
             cpu->x[r->rs1],cpu->x[r->rs2], cpu->x[r->rd]);
}
void execute_xor(CPU *cpu, R_Type *r){
     if (r->rd == 0) return;
     cpu->x[r->rd] = cpu->x[r->rs1] ^ cpu ->x[r->rs2];
     printf("[EXEC] XOR: x%d = x%d ^ x%d = 0x%08x ^ 0x%08x = 0x%08x\n",
               r->rd, r->rs1, r->rs2,
               cpu->x[r->rs1],cpu->x[r->rs2], cpu->x[r->rd]);
}
void execute_or(CPU *cpu, R_Type *r){
      if (r->rd == 0) return;

      cpu->x[r->rd] = cpu->x[r->rs1] | cpu ->x[r->rs2];
      printf("[EXEC] OR: x%d = x%d | x%d =  0x%08x | 0x%08x = 0x%08x\n",
              r->rd, r->rs1, r->rs2,
              cpu->x[r->rs1],cpu->x[r->rs2], cpu->x[r->rd]);
}
void execute_andi(CPU *cpu, I_Type *i){
     if(i->rd == 0) return;

     cpu->x[i->rd] = cpu->x[i->rs1]  & i->imm;
     printf("[EXEC] ANDI: x%d =x%d & 0x%x = 0x%08x\n",
            i->rd, i->rs1, i->imm, cpu->x[i->rd]);
 }
void execute_ori(CPU *cpu, I_Type *i){
       if(i->rd == 0) return;

       cpu->x[i->rd] = cpu->x[i->rs1]  | i->imm;
      printf("[EXEC] ORI: x%d =x%d | 0x%x = 0x%08x\n",
              i->rd, i->rs1, i->imm, cpu->x[i->rd]);
}
void execute_xori(CPU *cpu, I_Type *i){
         if(i->rd == 0) return;

        cpu->x[i->rd] = cpu->x[i->rs1]  ^ i->imm;
      printf("[EXEC] XORI: x%d =x%d ^ 0x%x = %08x\n",
               i->rd, i->rs1, i->imm, cpu->x[i->rd]); 
}
void execute_slti(CPU *cpu, I_Type *i){
       if(i->rd == 0) return;
       
       int32_t rs1_val = (int32_t)cpu->x[i->rs1];
       int32_t imm_val = i->imm;
       cpu->x[i->rd] = (rs1_val < imm_val ) ? 1 : 0;
       printf("[EXEC] SLTI: x%d =(x%d < %d) ? 1 : 0 = %u\n ",
               i->rd, i->rs1, i->imm, cpu->x[i->rd]);
}
void execute_sltiu(CPU *cpu, I_Type *i){
        if(i->rd == 0) return;

        cpu->x[i->rd] = (cpu->x[i->rs1]  < (uint32_t)i->imm) ? 1 : 0;
        printf("[EXEC] SLTIU: x%d =(x%d < %d) ? 1 : 0 = %u\n",
                 i->rd, i->rs1, i->imm, cpu->x[i->rd]);
}
void execute_srl(CPU *cpu, R_Type *r){
         if(r->rd == 0) return;
         uint32_t val = cpu ->x[r->rs1];
         uint32_t shift = cpu ->x[r->rs2] & 0x1F;
         cpu->x[r->rd] = val >> shift;
         printf("[EXEC]SRL : x%d = x%d >> %u = 0x%08x >> %u = 0x%08x\n"
                ,r->rd, r->rs1, shift, cpu->x[r->rs1], shift, cpu->x[r->rd]);
}
void execute_sll(CPU *cpu, R_Type *r){
         if(r->rd == 0) return;
         uint32_t val = cpu ->x[r->rs1];
         uint32_t shift = cpu ->x[r->rs2] & 0x1F;
         cpu->x[r->rd] = val << shift;
         printf("[EXEC]SLL : x%d = x%d << %u = 0x%08x << %u = 0x%08x\n",         r->rd, r->rs1, shift, cpu->x[r->rs1], shift, cpu->x[r->rd]);
}
void execute_sra(CPU *cpu, R_Type *r){
         if(r->rd == 0) return;
         int32_t val = cpu ->x[r->rs1];
         uint32_t shift = cpu ->x[r->rs2] & 0x1F;
         cpu->x[r->rd] = val >> shift;
         printf("[EXEC]SRA : x%d = x%d >> %u = 0x%08x >> %u = 0x%08x\n",         r->rd, r->rs1, shift, cpu->x[r->rs1], shift, cpu->x[r->rd]);
}
void execute_lw(CPU *cpu, Memory *mem, I_Type *i){
    if (i->rd == 0)return;
    uint32_t addr = cpu ->x[i->rs1] + i->imm;
    if (addr + 3 >= MEM_SIZE){
        printf("[ERROR] LW: Address out of bounds!\n");
        return;
    }
    
    cpu->x[i->rd] = mem->data[addr] |
                    (mem->data[addr + 1] << 8) |
                    (mem->data[addr + 2] << 16) |
                    (mem->data[addr + 3] << 24);
    printf("[EXEC] LW: x%d = Memory[x%d + x%d ] = Memory[0x%x] = 0x%08x\n", i->rd, i->rs1, i->imm, addr, cpu->x[i->rd]);
}
void execute_sw(CPU *cpu, Memory *mem, S_Type *s){
    uint32_t addr =cpu->x[s->rs1] + s->imm;
    if (addr + 3 >= MEM_SIZE){
        printf("[ERROR] SW: Address out of bounds!\n");
        return;
    }
    uint32_t val =cpu->x[s->rs2];
    mem->data[addr]     = val & 0xFF;
    mem->data[addr + 1] = (val >> 8) & 0xFF;
    mem->data[addr + 2] = (val >> 16) & 0xFF;
    mem->data[addr + 3] = (val >> 24) & 0xFF;
    printf("[EXEC] SW: Memory[x%d +%d] = x%d, Memory[0x%x] = 0x%08x\n",
            s->rs1, s->imm, s->rs2, addr, val);
}
void execute_beq(CPU *cpu,B_Type *b){
    if(cpu->x[b->rs1] == cpu ->x[b->rs2]){
        cpu->pc += b->imm;
        printf("[EXEC] BEQ: x%d == x%d，跳转到 pc=0x%x\n",
                b->rs1, b->rs2, cpu->pc);
    } else {
        cpu->pc += 4;
        printf("[EXEC] BEQ: x%d == x%d，不跳转到 pc=0x%x\n",
                b->rs1, b->rs2, cpu->pc);
    }
}
void execute_bne(CPU *cpu,B_Type *b){
     if(cpu->x[b->rs1] != cpu ->x[b->rs2]){
         cpu->pc += b->imm;
         printf("[EXEC] BNE: x%d != x%d，跳转到 pc=0x%x\n",
                 b->rs1, b->rs2, cpu->pc);
     } else {
         cpu->pc += 4;
         printf("[EXEC] BNE: x%d == x%d，不跳转到 pc=0x%x\n",
                 b->rs1, b->rs2, cpu->pc);
     }
}
void execute_blt(CPU *cpu,B_Type *b){
    int32_t val1 =(int32_t)cpu->x[b->rs1];
    int32_t val2 =(int32_t)cpu->x[b->rs2];
    if(val1 < val2 ){
        cpu->pc += b->imm;
        printf("[EXEC] BLT: x%d(%d) < x%d(%d), 跳转到 pc=ox%x\n",
                b->rs1, val1, b->rs2,val2, cpu->pc);
    } else {
        cpu->pc += 4;
        printf("[EXEC] BLT: x%d(%d) >= x%d(%d),不跳转, pc=0x%x\n",
                b->rs1, val1, b->rs2,val2, cpu->pc);
    }
}
void execute_bge(CPU *cpu, B_Type *b) {
      int32_t val1 = (int32_t)cpu->x[b->rs1];
      int32_t val2 = (int32_t)cpu->x[b->rs2];

      if (val1 >= val2) {
          cpu->pc += b->imm;
          printf("[EXEC] BGE: x%d(%d) >= x%d(%d), 跳转到 PC=0x%x\n",
                 b->rs1, val1, b->rs2, val2, cpu->pc);
      } else {
          cpu->pc += 4;
          printf("[EXEC] BGE: x%d(%d) < x%d(%d), 不跳转, PC=0x%x\n",
                 b->rs1, val1, b->rs2, val2, cpu->pc);
      }
}
void execute_jalr(CPU *cpu, I_Type *i){
 instruction_count++;
    uint32_t target_addr = (cpu->x[i->rs1] + i->imm) & ~1;
    if(i->rd != 0){
            cpu->x[i->rd] = cpu->pc +4;}

    cpu->pc = target_addr;
    printf("[EXEC] JALR: x%d = 0x%x (return addr)\n", i->rd,cpu->x[i->rd]);
    printf("PC= (x%d;%d + %d) & ~1 = 0x%x\n",i->rs1, cpu->x[i->rs1],i->imm,cpu->pc);
}
void execute_jal(CPU *cpu, J_Type *j){
 instruction_count++;
  function_calls++;
    printf("[EXEC] JAL x%d, %d\n", j->rd, j->imm);
    uint32_t target_addr = (cpu->pc + j->imm ) ;
    
    if(j ->rd != 0){
        cpu->x[j->rd] = cpu->pc + 4;
        printf(" -> Save return address: x%d = 0x%x\n", j->rd, cpu->x[j->rd]);}
    cpu->pc = target_addr;
    printf(" -> Jump to: 0x%x\n", cpu->pc);
}
