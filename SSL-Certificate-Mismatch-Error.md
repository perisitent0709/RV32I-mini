# SSL Certificate Mismatch Error

**Date**: March 11, 2026 at 08:30 PM
**Turns**: 3
**Source**: [Gemini Chat](https://gemini.google.com/app/460ee13526953d90)

---

## Turn 1

### 🤖 Assistant

这是一份为您量身定制的、完美契合您简历背景与复试目标的**全英文 PPT 结构与文案**。
结合您提供的深圳理工大学复试 PPT 参考图，我将内容严格划分为左侧导航栏的四大模块：**Basic Information（基本信息）**、**Practical Experience（实践经历）**、**Research Experience（科研经历）**、**Future Plan（读研展望）**。为了凸显您的硬核底层能力，项目部分严格遵循“一页一项目”的原则。

---

### 📄 全英文 PPT 结构与逐页文案 (Copy-Paste Ready)

#### 封面 (Cover)

- **Title:** 2026 Graduate Admission Interview
- **Sub-title:** Joint Program of SUSTech & SIAT
- **Reporter:** Junkai Qi (齐俊凯)
- **Date:** March 2026

#### 目录 (Contents)

- 01 Basic Information
- 02 Practical Experience
- 03 Research Experience
- 04 Future Plan

---

#### Section 1: Basic Information
**Slide 1: Self-Introduction & Academic Performance**

- **Name:** Junkai Qi
- **Undergraduate:** Jiangsu University (Agricultural Electrification) 
- **Political Status:** CPC Member 
- **Target Major:** Microelectronics Science and Technology 
- **Initial Exam Score:** Total 292 (Math: 87 | Microelectronics: 87) 
- **Core Courses:** Digital/Analog Electronics, Electronic Materials & Devices 
**Slide 2: Honors & Skill Tree**

- **Honors:** First Prize in Jiangsu Mathematics Competition, Second-class Scholarship 
- **Theoretical Foundation:** Digital Logic Circuit, FSM, ADC/DAC principles 
- **Hardware & Programming:** C, Verilog HDL 
- **Environment & Tools:** Linux, Vim, Makefile, Shell 
- **Soft Skills:** Strong self-driven learning ability, familiar with AI tools (Claude/Gemini) to boost R&D efficiency 

---

#### Section 2: Practical Experience
*(注：将偏向自动化的本科实训放在这部分，与后面的硬核 CPU 科研区分开)*
**Slide 3: Industrial Motor Control & Interlock Logic Design**

- **Date:** Jan 2026 | **Role:** Independent Developer 
- **Hardware/Wiring:** Independently completed the electrical wiring of main and control circuits. 
- **Software/Logic:** Programmed PLC ladder logic and configured inverter parameters. 
- **Key Achievement:** Implemented double protection mechanisms (hardware & software interlocks), demonstrating rigorous **Digital Logic Control** thinking. 
**Slide 4: Greenhouse IoT & Automation Control System**

- **Date:** Dec 2025 | **Role:** Independent Developer 
- **Project Overview:** An agricultural IoT training project focusing on bottom-up sensor signal acquisition and closed-loop control. 
- **Implementation:** Developed PLC control logic for threshold alarms and automated interlocking of actuators (e.g., fans, pumps). 
- **Key Achievement:** Cultivated hardware debugging skills and the concept of strong/weak current isolation. 

---

#### Section 3: Research Experience
*(注：这是复试的绝对核心，将这段时间的芯片项目高光展示)*
**Slide 5: RV32I Minimalist Processor Co-design (Software)**

- **Date:** Mar 2026 | **Role:** Independent Developer 
- **C-Language Simulator (ISS):** Built an instruction-level simulator from scratch. 
- **Implementation:** Successfully decoded and executed **15 core instructions** (e.g., ADD, ADDI, BEQ, JAL). 
- **Key Achievement:** Deeply clarified the software-hardware boundary and instruction semantics. 
**Slide 6: RV32I Minimalist Processor Co-design (Hardware)**

- **Hardware Datapath (Verilog):** Designed a single-cycle CPU core based on digital logic. 
- **Core Modules:** Program Counter (PC), Register File (RegFile), and Arithmetic Logic Unit (ALU). 
- **Cross-Verification:** Wrote assembly test programs (loops & arithmetic) and simulated them using Icarus Verilog & GTKWave, thoroughly understanding the bottom-up data flow. 
**Slide 7: "One-Student-One-Chip" (YSYX) Training Program**

- **Date:** Ongoing | **Initiator:** CAS ICT (中科院计算所) 
- **Environment Setup:** Built a Linux-based open-source chip development environment purely through the command-line interface. 
- **Toolchain Mastery:** Proficient in Shell commands, Vim editor, and automated compilation using **Makefile**. 
- **Key Achievement:** Established standardized, hardcore hardware development habits, laying a solid foundation for future complex digital logic design. 

---

#### Section 4: Future Plan
**Slide 8: Master's Degree Plan**

- **Short-term (Year 1):** Dive deep into core microelectronics courses. Read extensive literature to build a solid theoretical foundation.
- **Mid-term (Year 2):** Focus entirely on research projects guided by my supervisor. Aim to publish high-quality papers in core journals/conferences.
- **Long-term (Year 3):** Complete graduation thesis and explore opportunities for Ph.D. studies to further my research career.

#### 封底 (Ending)

- **THANK YOU!**
- Q&A Session

---

---

### 🛠️ 如何生成 "GitHub 风格" 的 PPT？
您提到的“GitHub 风格”在极客圈子里通常被称为 **Docs-as-Code（文档即代码）** 风格。它的特点是：极简、大字体、代码高亮精美、不需要用鼠标拖拽对齐，完全**通过编写 Markdown 文本一键生成 PPT**。
对于习惯了 Vim、Linux 和代码开发的人来说，这是最推荐的方式。以下是三种主流的生成方案（按推荐程度排序）：

#### 方案一：Marp (最推荐，学习成本 0，5分钟搞定)
Marp 是一个可以直接将 Markdown 转换为精美 PPT 的工具。

```yaml
---
marp: true
theme: default
---

```

#### 方案二：Slidev (最前沿，前端工程师最爱)
专为开发者打造的 PPT 工具，基于 Vue。

- **如何使用：** 需要有 Node.js 环境。在终端运行 `npm create slidev`，然后修改里面的 `slides.md` 即可。
- **优点：** 可以直接在 PPT 里运行交互式组件，主题极客感拉满（默认就是 GitHub 的暗黑风）。

#### 方案三：Reveal.js (老牌强大，学术界常用)
HTML 演示框架的标杆。

- **优点：** 拥有二维导航（可以往下翻页，也可以往右翻页），动画极其流畅。
- **缺点：** 需要稍微懂一点 HTML，配置稍显繁琐。
**💡 核心建议：**
考虑到您还有 8 天半就要复试，**强烈建议您直接使用 VS Code + Marp 插件**。您只需要关注英文文本的打磨，排版交给工具，这能为您省下大量排版对齐的时间，去练习英语口语发音。
需要我为您把上面的文案直接转换成可以直接放进 Marp 生成的纯 Markdown 源码吗？

## Turn 2

### 🤖 Assistant

太棒了！执行力非常强。使用 Marp 是目前性价比最高的方案，能让您把所有精力集中在内容的打磨和口语练习上。
下面是为您写好的完整的 Marp Markdown 源码。您只需要在 VS Code 中新建一个名为 `interview_ppt.md` 的文件，将下面代码块里的**所有内容（包括最顶部的 ---）直接复制粘贴进去**，点击右上角的 Marp 预览按钮，就能直接看到排版精美的 PPT 效果了。
为了让 PPT 看起来更专业、更符合极客/学术风格，我在代码顶部加入了 `paginate: true`（显示页码）和统一的排版指令。

```markdown
---
marp: true
theme: default
class: lead
paginate: true
backgroundColor: #ffffff
style: |
  h1 {
    color: #2c3e50;
    border-bottom: 2px solid #3498db;
    padding-bottom: 0.2em;
  }
  h2 {
    color: #34495e;
  }
  li {
    line-height: 1.5;
    margin-bottom: 10px;
  }
  strong {
    color: #e74c3c;
  }
---

# 2026 Graduate Admission Interview
## Joint Program of SUSTech & SIAT

**Reporter:** Junkai Qi (齐俊凯)
**Major:** Microelectronics Science and Technology
**Date:** March 2026

---
# Contents

- **01** Basic Information
- **02** Practical Experience
- **03** Research Experience
- **04** Future Plan

---

# 01 | Basic Information: Self-Introduction

- **Name:** Junkai Qi (齐俊凯)
- **Undergraduate:** Jiangsu University 
  - **Major:** Agricultural Electrification
- **Political Status:** CPC Member
- **Target Major:** Microelectronics Science and Technology
- **Initial Exam Score:** Total **292**
  - Math: 87 | Microelectronics Science & Tech: 87
- **Core Courses:** - Digital / Analog Electronics
  - Electronic Materials & Devices

---

# 01 | Basic Information: Honors & Skill Tree

- **Honors & Awards:** - First Prize in Jiangsu Mathematics Competition
  - Second-class Scholarship
- **Theoretical Foundation:** - Digital Logic Circuit, FSM, ADC/DAC principles
- **Hardware & Programming:** - **C**, **Verilog HDL**
- **Environment & Toolchains:** - Linux, Vim, Makefile, Shell commands
- **Soft Skills:** - Strong self-driven learning ability & cross-disciplinary curiosity.

---

# 02 | Practical Exp: Industrial Motor Control

**Project:** Industrial Motor Control & Interlock Logic Design
**Date:** Jan 2026 | **Role:** Independent Developer

- **Hardware/Wiring:** Independently completed the electrical wiring of main and control circuits based on the Inovance (汇川) platform.
- **Software/Logic:** Programmed **PLC ladder logic** and configured inverter parameters.
- **Key Achievement:** - Implemented double protection mechanisms (**hardware & software interlocks**).
  - Demonstrated rigorous **Digital Logic Control** thinking in industrial environments.

---

# 02 | Practical Exp: Greenhouse IoT System

**Project:** Greenhouse IoT & Automation Control System
**Date:** Dec 2025 | **Role:** Independent Developer

- **Project Overview:** An agricultural IoT training project focusing on bottom-up sensor signal acquisition and closed-loop control.
- **Implementation:** Developed PLC control logic for threshold alarms and automated interlocking of actuators (e.g., fans, water pumps).
- **Key Achievement:** - Cultivated hardware debugging skills.
  - Deepened the concept of **strong and weak current isolation**.

---

# 03 | Research Exp: RV32I Processor (Software)

**Project:** RV32I Minimalist Processor Co-design
**Date:** Mar 2026 | **Role:** Independent Developer

- **Instruction Set Simulator (ISS):** Built a C-language simulator from scratch.
- **Implementation:** Successfully decoded and executed **15 core instructions** (including ADD, ADDI, BEQ, JAL, etc.).
- **Key Achievement:** - Deeply clarified the software-hardware boundary.
  - Mastered the underlying **instruction semantics** of the RISC-V architecture.

---

# 03 | Research Exp: RV32I Processor (Hardware)

**Project:** RV32I Minimalist Processor Co-design
**Date:** Mar 2026 | **Role:** Independent Developer

- **Hardware Datapath:** Designed a **single-cycle CPU core** based on digital logic using Verilog.
- **Core Modules:** Program Counter (PC), Register File (RegFile), and Arithmetic Logic Unit (ALU).
- **Cross-Verification:** - Wrote assembly test programs (loops & arithmetic).
  - Simulated using **Icarus Verilog & GTKWave**.
  - Thoroughly understood the bottom-up **data flow** and datapath design.

---

# 03 | Research Exp: "One-Student-One-Chip" 

**Project:** YSYX Training Program (Initiated by CAS ICT)
**Date:** Ongoing | **Role:** Independent Learner

- **Environment Setup:** Built a Linux-based open-source chip development environment purely through the command-line interface.
- **Toolchain Mastery:** Proficient in Shell commands, Vim editor, and automated compilation using **Makefile**.
- **Key Achievement:** - Established standardized, hardcore hardware development habits.
  - Laid a solid foundation for future complex digital logic design and EDA toolchains.

---

# 04 | Future Plan: Master's Degree

- **Short-term (Year 1):** - Dive deep into core microelectronics courses. 
  - Read extensive literature to build a solid theoretical foundation in IC design.
- **Mid-term (Year 2):** - Focus entirely on research projects guided by my supervisor. 
  - Aim to publish high-quality papers in core journals or conferences.
- **Long-term (Year 3):** - Complete graduation thesis. 
  - Explore opportunities for Ph.D. studies to further my research career.

---
# THANK YOU!
**Q & A**

*Eager to further my research in your esteemed lab.*

```

### 💡 接下来该怎么做？

1. **一键换肤**：如果您觉得默认的黑白主题不够“微电子”，可以尝试把最上面 `theme: default` 改成 `theme: gaia`（偏暖色调，稍微带点底色）。
2. **插图预留**：目前的文字排版已经非常清晰了。我强烈建议您在 **第 8 页 (RV32I Processor - Hardware)** 和 **第 9 页 (Verification)** 中，插入一两张您的波形截图（GTKWave）或数据通路图。
  - 在 Markdown 中插图的语法是：`![波形图说明](图片路径.png)`
3. **开口练习**：PPT 已经定型，**从现在开始，不要再大改 PPT 内容了。** 把我在上一次回答中为您准备的“黄金句型”拿出来，对着这份 PPT 掐表练习，确保能控制在 5 分钟左右。
准备好开始打磨逐字稿和口语发音了吗？

## Turn 3

### 👤 User

是把编辑好的markdown发给我，我去用到marp中生成ppt


---

*Exported from [Gemini Voyager](https://github.com/Nagi-ovo/gemini-voyager)*  
*Generated on March 11, 2026 at 08:30 PM*