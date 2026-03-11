#include <stdio.h>
#include <stdint.h> // 提供 uint32_t, uint8_t 等标准数据类型的定义

int main() {
    // 我们的目标机器码: ADDI x1, x0, 10
    uint32_t inst = 0x00A00093; 

    // 1. 提取 opcode (第 0~6 位，共 7 位)
    // 0x7F 的二进制是 0000...01111111 (连续7个1)
    uint8_t opcode = inst & 0x7F;

    // 2. 提取 rd (第 7~11 位，共 5 位)
    // 右移 7 位将 rd 挪到最右边，0x1F 是 5 个 1 (二进制 11111)
    uint8_t rd = (inst >> 7) & 0x1F;

    // 3. 提取 funct3 (第 12~14 位，共 3 位)
    // 右移 12 位，0x7 是 3 个 1 (二进制 111)
    uint8_t funct3 = (inst >> 12) & 0x7;

    // 4. 提取 rs1 (第 15~19 位，共 5 位)
    // 右移 15 位，0x1F 是 5 个 1
    uint8_t rs1 = (inst >> 15) & 0x1F;

    // 5. 提取立即数 imm (第 20~31 位，共 12 位)
    // 注意：在 RISC-V 中，立即数是有符号的（可能为负数）。
    // 将无符号的 inst 强制转换为有符号的 int32_t，
    // 然后进行算术右移，C语言会自动保留符号位（最高位），完美实现符号扩展！
    int32_t imm = ((int32_t)inst) >> 20;

    // 打印结果验证
    printf("Instruction: 0x%08X\n", inst);
    printf("---------------------------\n");
    printf("opcode = 0x%02X\n", opcode);
    printf("rd     = %d\n", rd);
    printf("funct3 = %d\n", funct3);
    printf("rs1    = %d\n", rs1);
    printf("imm    = %d\n", imm);

    return 0;
}
