# 🚀 System Programming Lab 1

**Course:** System Programming Laboratory (202-1-2131)
**Submitted by:** Reem Schur

---

## 📜 Project Description

This project is the submission for Lab 1 in the System Programming course. It demonstrates foundational concepts of memory manipulation in C, including:
* Analysis of process memory layout (Stack, Heap, Code, Data).
* Usage of pointers, including pointer arithmetic.
* Dynamic memory management (`malloc` and `free`).
* Simulation of Object-Oriented Programming (OOP) using `struct`s and function pointers.

---

## 💡 Core Features

The project is divided into several tasks:

### Task 0: `count-words`
* A basic program intended for practicing bug detection (`Segmentation Fault`) using the `gdb` debugger.

### Task 1: `addresses`
* A program that prints the memory addresses of various variable types (local, global, static, functions) to illustrate the process memory layout.
* Demonstrates pointer arithmetic on different data types.

### Tasks 2 & 3: `menu_map`
This is the main program of the lab.
* **Interactive Menu System:** Runs in a persistent loop.
* **Generic `map` Function:** Accepts a function pointer to apply a transformation to each element in an array.
* **Memory Management:** Correctly uses `malloc` for new arrays and `free` for old ones to prevent memory leaks.
* **Object Simulation:** Uses a `struct` (`MenuOption`) to link a display name to a corresponding function pointer.
* **Functionality:**
    * **Get string:** Reads a new string from the user.
    * **Print dec:** Prints the decimal (ASCII) value of each character.
    * **Print string+hex:** Prints the character and its hexadecimal value.
    * **Encrypt / Decrypt:** Applies a simple `+1` / `-1` cipher to each character.

---

## 🔧 Tech Stack & Environment

* **Language:** C (C11 standard)
* **Compiler:** `gcc`
* **Build Tool:** `make`
* **Debugger:** `gdb`
* **Runtime Environment:** The official course Virtual Machine (Lubuntu 32-bit).

---

## 🚀 How to Run

This project must be compiled and run within the course's Linux VM environment.

### 1. Compile

Open a terminal in the project's root directory (`system-programming-lab-one`) and type:

```bash
make

cd task3
./menu_map

./addresses

make clean

