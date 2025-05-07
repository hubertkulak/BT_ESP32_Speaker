# BT_ESP32_Speaker
BT_ESP32_Speaker

# Wireless Class D Audio Amplifier System

This project showcases the design and development of two audio-related hardware systems based on Class D amplifiers, using C and ESP32 microcontroller technology. It was created as part of a diploma thesis combining passion for electronics, music, and embedded systems development.

Repositorium contains code for ESP-IDF project wirtten in C language for ESP32 bluetooth stereo audio amplifier.

## 🔧 Project Overview

The project consists of two main parts:

### 1. **Bluetooth Stereo Audio Board**
A four-layer PCB integrating two MAX98357A Class D amplifiers, configured for stereo output. Audio data is wirelessly transmitted via Bluetooth using an ESP32 microcontroller and the I2S interface.

- Features:
  - Bluetooth audio streaming
  - I2S communication
  - ESP32-based firmware
  - Designed in Altium Designer
![image](https://github.com/user-attachments/assets/327f2730-5afd-4592-803f-112ef22979b2)

### 2. **Amplifier Testing Board**
A two-layer research PCB containing three different Class D amplifiers (e.g. PAM8019KGR, TPA2008D2), created for the purpose of measuring key parameters such as:
- SNR (Signal-to-Noise Ratio)
- THD (Total Harmonic Distortion)
- Frequency response

![image](https://github.com/user-attachments/assets/ec0b80a8-1755-4f35-b50a-5e34665d6c1b)


## 🧪 Capabilities

- Carried out PCB design and simulation in Altium Designer
- Developed embedded software for ESP32 (ESP-IDF framework)
- Performed hardware testing with oscilloscopes and signal analyzers
- Implemented audio streaming with wireless communication
- Conducted signal integrity measurements and amplifier comparison

## 🛠 Technologies

- Python (for auxiliary tools)
- ESP32 + ESP-IDF
- I2S audio interface
- Bluetooth A2DP
- Altium Designer (PCB design)
- Pygame (for simulation, if needed)

## 📁 Structure

- `hardware/` – PCB schematics and layouts (Altium)
- `firmware/` – ESP32 source code (C/C++)
- `measurements/` – SNR, THD graphs and oscilloscope screenshots

---

> This project demonstrates the practical integration of embedded systems with modern audio amplifier technology, focusing on both design and measurement aspects of wireless Class D audio devices.
