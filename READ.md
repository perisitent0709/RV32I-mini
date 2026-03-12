# 🚀 RV32I-Mini Processor Co-Design

> **A minimalist RISC-V processor implemented via software-hardware co-design.**
> Developed as a comprehensive practice for understanding Computer Architecture and Digital Logic Design.

## 🌟 Project Overview
This project bridges the gap between theoretical Instruction Set Architecture (ISA) and practical RTL implementation. It contains two major parts: an instruction-level simulator written in C, and a single-cycle CPU datapath written in Verilog HDL.

### 1. Software Simulator (`/c_simulator`)
Built from scratch to verify the decoding logic and instruction semantics.
- **Supported Instructions (15 core instructions):** - Arithmetic/Logic: `ADD`, `SUB`, `ADDI`, `AND`, `OR`, `XOR`, `ANDI`, `ORI`, `XORI`
  - Shift: `SLL`, `SRL`, `SRA`
  - Memory: `LW`, `SW`
  - Branch: `BEQ`
- **Capabilities:** Successfully executes loops and basic arithmetic algorithms (e.g., Fibonacci sequence).

### 2. Hardware Datapath (`/verilog_rtl`)
A digital logic implementation of the RV32I single-cycle microarchitecture.
- **Core Modules:**
  - `pc.v`: Program Counter
  - `imem.v` & `dmem.v`: Instruction & Data Memory
  - `regfile.v`: 32x32-bit Register File
  - `alu.v`: Arithmetic Logic Unit
  - `cpu_top.v`: Top-level datapath integration
- **Verification:** Simulated using **Icarus Verilog** and visualized with **GTKWave**. The hardware output strictly matches the C-simulator results.

## 📂 Repository Structure
```text
📦 RV32I-Mini
 ┣ 📂 c_simulator       # C language instruction-level simulator
 ┣ 📂 verilog_rtl       # Verilog modules for the single-cycle CPU
 ┗ 📜 README.md         # Project documentation
