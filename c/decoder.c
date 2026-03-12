#include "riscv.h"
void decode_r_type(uint32_t inst,R_Type *r){
    r->opcode = inst & 0x7F;
    r->rd = (inst >> 7) & 0x1F;
    r->funct3 = (inst >> 12) & 0x7;
    r->rs1 = (inst >> 15) & 0x1F;
    r->rs2 = (inst >> 20) & 0x1F;
    r->funct7 = (inst >>25) & 0x7F;
    printf("[DECODE] R-Type: opcode=0x%02x, rd=x%d, rs1=x%d, rs2=x%d, funct3=0x%x, funct7=0x%x\n",
           r->opcode, r->rd, r->rs1, r->rs2, r->funct3, r->funct7);}
void decode_i_type(uint32_t inst,I_Type *i){
    i->opcode = inst & 0x7F;
    i->rd = (inst >> 7) & 0x1F;
    i->funct3 = (inst >> 12) & 0x7;
    i->rs1 = (inst >>15 ) & 0x1F;
    int32_t imm_raw = (inst >> 20) & 0xFFF;
    if (imm_raw & 0X800 ){
        i->imm = imm_raw | 0xFFFFF000;
    } else {
        i->imm = imm_raw;
    }

    printf("[DECODE] I-Type: opcode=0x%02x,rd=x%d, rs1=x%d, imm=%d\n",
            i->opcode, i->rd, i->rs1, i->imm);
}
void decode_s_type(uint32_t inst,S_Type *s){
    s->opcode = inst & 0x7F;
    s->funct3 = (inst >> 12) & 0x7;
    s->rs1 = (inst >> 15) & 0x1F;
    s->rs2 = (inst >> 20) & 0x1F;

    int32_t imm_11_5 = (inst >> 25) & 0x7F;
    int32_t imm_4_0 = (inst >> 7) & 0x1F;

    int32_t imm_raw = (imm_11_5 << 5) | imm_4_0;

    if (imm_raw & 0x800) {
        s->imm = imm_raw | 0xFFFFF000;
    } else {
        s->imm = imm_raw;
    }
    printf("[DECODE] S-Type: opcode=0x%02x, rs1=x%d, rs2=x%d, imm=%d\n",
         s->opcode, s->rs1, s->rs2, s->imm);
}
void decode_b_type(uint32_t inst, B_Type *b){
    b->opcode = inst & 0x7F;
    b->funct3 = (inst >> 12) & 0x7;
    b->rs1 = (inst >> 15) & 0x1F;
    b->rs2 = (inst >> 20) & 0x1F;

    int32_t imm_12 =(inst >>31 ) & 0x1;
    int32_t imm_11 =(inst >>7 ) & 0x1;
    int32_t imm_10_5 =(inst >>25 ) & 0x3F;
    int32_t imm_4_1 =(inst >>8 ) & 0xF;
    
    int32_t imm_raw = (imm_12 << 12) | (imm_11 << 11) | (imm_10_5 << 5) |
                      (imm_4_1 << 1);
    if (imm_raw & 0x1000){
        b->imm = imm_raw | 0xFFFFE000;
    } else{
        b->imm = imm_raw;
    }
     printf("[DECODE] B-Type: opcode=0x%02x, rs1=x%d, rs2=x%d, imm=%d\n"            ,b->opcode, b->rs1, b->rs2, b->imm);
}
void decode_j_type(uint32_t inst,J_Type *j){
    j->opcode = inst & 0x7F;
    j->rd = (inst >> 7) & 0x1F;

    int32_t imm_20 = (inst >> 31) & 0x1;
    int32_t imm_10_1 = (inst >> 21) & 0x3FF;
    int32_t imm_11 = (inst >> 20) & 0x1;
    int32_t imm_19_12 = (inst >> 12) & 0xFF;

    int32_t imm_raw = (imm_20 << 20) | (imm_19_12 << 12) |(imm_11 << 11)                        | (imm_10_1 << 1);
    if (imm_raw & 0x100000) {
        j->imm = imm_raw | 0xFFE00000;
    } else {
        j->imm = imm_raw;
    }

    printf("[DECODE] J-Type: opcode=0x%02x, rd=x%d, imm=%d (0x%x)\n",
            j->opcode, j->rd, j->imm, j->imm);
}

