# 🚀 CPU Pipeline Simulation using Arduino & LCD

## 🔥 Overview
This project simulates a **basic CPU pipeline** using an **Arduino Uno**, an **LCD display**, and **LED indicators**. It visualizes the execution of assembly-like instructions with a step-by-step pipeline process (Fetch, Decode, Execute, Memory). Users can input commands via the **Serial Monitor**, and the system processes them accordingly.

**💡 Done using:** [Tinkercad](https://www.tinkercad.com/) (Simulation)

---

## 🎯 Features
✅ **Instruction Processing** - Supports basic assembly-like instructions like `MOV`, `ADD`, `SUB`, and `HLT`.

✅ **Pipeline Stages** - Implements Fetch, Decode, Execute, and Memory stages with **LED indicators**.

✅ **LCD Display** - Shows real-time execution stages and register values.

✅ **Push Button Execution** - Steps through the pipeline with a **button press**.

✅ **Serial Monitor Input** - Accepts instructions from the user via Arduino Serial Monitor.

---

## ⚙️ Components Used
- **Arduino Uno**
- **I2C LCD Display**
- **Push Button**

- **LEDs (Red, Yellow, Green)**
- **Resistors & Jumper Wires**

📌 Circuit design
![Screenshot 2025-02-17 213817](https://github.com/user-attachments/assets/49c6176f-ec8d-4644-b7c2-056f66b0cf02)

📌 Circuit diagram 

![Screenshot 2025-02-17 213832](https://github.com/user-attachments/assets/cf8288f7-d4c8-4e8d-a198-00997d39cca3)

---

## 📜 How It Works
1. Enter an instruction in the **Serial Monitor** (Example: `MOV A,5` or `ADD`).
2. Press the **Push Button** to execute the instruction step-by-step.
3. The LCD and LEDs will indicate the **current stage** of execution.
4. The final register values are displayed on the LCD.
5. The program stops when `HLT` is entered.

---

## 📂 Code
The Arduino code is available in the repository.
- `cpu_pipeline.ino` - The main Arduino script.
- `tinkercad_code.txt` - Code compatible with **Tinkercad Simulation**.
- `arduino_ide_code.ino` (optional) - For direct upload to **Arduino Uno**.

---

## 🔗 Setup Guide
1. Clone the repository:
   ```sh
   git clone https://github.com/Abin-Shaji-Thomas/CPU-Pipeline-Simulation-using-Arduino-LCD.git
   ```
2. Open `cpu_pipeline.ino` in **Arduino IDE**.
3. Connect your Arduino hardware and upload the code.
4. Open the **Serial Monitor** and send instructions.
5. Press the **Push Button** to execute them!

---

## 🔒 License
This project is **MIT Licensed**, but **direct copying** of the repository is restricted.

📢 _If you want to use or modify this project, please provide proper attribution!_

---

## 🛠 Future Improvements
🚀 Add more assembly-like instructions.

🚀 Integrate IoT-based remote instruction input.

🚀 Improve UI with an OLED Display.

---

## ❤️ Contribute
Feel free to **fork**, **star**, and **contribute** to this project!



---

