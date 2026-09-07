# STM32F407VG Bare-Metal Programming

This repository contains my **bare-metal Embedded C programs and practical implementations for the STM32F407VG microcontroller**.

The programs are developed as part of my learning and practice based on the **Embedded Systems Bare Metal Programming** course on Udemy.

The main objective of this repository is to understand the STM32F407VG at the **register level** and develop a strong foundation in embedded firmware development without depending on high-level peripheral libraries.

## 🎯 Objectives

* Understand STM32F407VG microcontroller architecture
* Learn ARM Cortex-M4 fundamentals
* Understand peripheral registers and memory-mapped I/O
* Develop firmware using Embedded C
* Practice direct register-level programming
* Understand interrupts and exception handling
* Interface and configure STM32 peripherals
* Build a strong foundation for Embedded Software/Firmware development

## 🛠️ Microcontroller

**STM32F407VG**

* ARM Cortex-M4 based MCU
* 32-bit architecture
* STM32F4 family
* Embedded C programming
* Register-level peripheral programming

## 📚 Topics Covered

### GPIO

* GPIO clock configuration
* GPIO input/output configuration
* LED control
* Push-button input
* GPIO registers
* Bit manipulation

### Clock Configuration

* RCC
* HSI
* HSE
* PLL
* System clock configuration
* Peripheral clock enable

### Interrupts

* Interrupt fundamentals
* NVIC
* Interrupt service routines
* External interrupts
* EXTI

### Timers

* Basic timers
* Timer configuration
* Timer interrupts
* Delay generation
* PWM

### UART

* USART/UART configuration
* Baud rate configuration
* Transmit and receive
* Polling
* Interrupt-based communication

### SPI

* SPI configuration
* Master mode
* Data transmission and reception
* SPI communication

### I2C

* I2C fundamentals
* Master communication
* Start/Stop conditions
* Data transmission and reception

### ADC

* ADC configuration
* Analog-to-digital conversion
* ADC channels
* Polling and conversion handling

### DMA

* DMA fundamentals
* Memory-to-peripheral transfer
* Peripheral-to-memory transfer
* DMA configuration

### CAN

* CAN fundamentals
* CAN peripheral configuration
* CAN message transmission
* CAN message reception

### Other Embedded Concepts

* Memory-mapped registers
* Bit manipulation
* Volatile variables
* Startup code
* Linker concepts
* Interrupt vector table
* ARM Cortex-M4 fundamentals
* Embedded firmware structure

## 📁 Repository Structure

```text
STM32F407VG-BareMetal/
│
├── GPIO/
├── CLOCK/
├── INTERRUPT/
├── TIMER/
├── UART/
├── SPI/
├── I2C/
├── ADC/
├── DMA/
├── CAN/
└── README.md
```

> The directory structure may evolve as more peripherals and concepts are added.

## 💻 Development Environment

* **Microcontroller:** STM32F407VG
* **Programming Language:** Embedded C
* **Architecture:** ARM Cortex-M4
* **IDE:** STM32CubeIDE
* **Compiler:** ARM GCC
* **Debugger/Programmer:** ST-LINK
* **Operating System:** Linux

## 🔧 Programming Approach

The primary focus of this repository is **bare-metal programming**.

Instead of relying on high-level HAL APIs, the programs focus on understanding and configuring peripherals through their hardware registers.

For example:

```c
RCC->AHB1ENR |= (1U << 3);

GPIOD->MODER &= ~(3U << (12 * 2));
GPIOD->MODER |=  (1U << (12 * 2));

GPIOD->ODR ^= (1U << 12);
```

This approach helps in understanding:

* Register addresses
* Register bit fields
* Peripheral clock control
* GPIO configuration
* Bit manipulation
* Hardware-level firmware operation

## 📈 Learning Progress

| Topic       | Status                    |
| ----------- | ------------------------- |
| GPIO        | 🟢 Completed / Practicing |
| RCC & Clock | 🟡 Learning               |
| Interrupts  | 🟡 Learning               |
| Timers      | 🟡 Learning               |
| UART        | 🟡 Learning               |
| SPI         | 🟡 Learning               |
| I2C         | 🟡 Learning               |
| ADC         | 🟡 Learning               |
| DMA         | 🟡 Learning               |
| CAN         | 🟡 Learning               |

This table will be updated as I progress through the topics.

## 🎓 Learning Resource

This repository is based on concepts and practical learning from the following Udemy course:

**Embedded Systems Bare Metal Programming**

[Udemy Course](https://www.udemy.com/course/embedded-systems-bare-metal-programming/)

## 🚀 Goal

The long-term goal of this repository is to build strong practical knowledge in:

**Embedded C → ARM Cortex-M → STM32 → Bare-Metal Firmware → Embedded Software Development**

and use these concepts to develop reliable and efficient embedded firmware for real-world applications.

## 👨‍💻 Author

**Nilanshu Dashwath**

Embedded Software / Embedded AI Developer

---

⭐ This repository is continuously updated as I learn and implement new STM32F407VG bare-metal concepts.
