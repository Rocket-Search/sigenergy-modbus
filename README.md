# Sigenergy Modbus Tool

A simple tool for reading values from a Sigenery (SigenStor) device using the Modbus protocol.  
This tool is built on top of [`libmodbus`](https://libmodbus.org/).

Two configuration files are included, containing all the read-only and read-write register addresses according to the official Sigenery Modbus specifications.

📄 You can reach Sigenery support for the official Modbus protocol documentation here:  
👉 https://www.sigenergy.com/en/contact




## ⚙️ How It Works

### 1. Compile the tool


g++ -g -O3 -fPIC -Wall -std=c++20 -fpermissive -c -o sigenergy_modbus.o sigenergy_modbus.cpp



### 2. Link the binary

g++ -O3 -fPIC -Wall -o sigenergy_modbus sigenergy_modbus.o -lmodbus



### 3. Run the tool
./sigenergy_modbus config_sigenergy_register_addresse_slave_247.cfg 247 192.168.188.69 502

Replace the configuration file, slave ID, IP address, and port according to your setup.


## ℹ️ Info

This tool runs independently from the official Sigenery app.
However, Modbus support must be enabled by either Sigenery support or the technician who installed your system.

## ✅ To Do

better error handling

Grafana integration

RRDTool integration

create a user interface:

- Qt?

- Java?

- WxWidgets?

add units to displayed values (based on config file)

show valid value ranges (based on config file)

create a makefile for simplified builds

## 🧪 Test Environment

- **Device:** Raspberry Pi 3B Rev 1.2  
- **Compiler:** `g++ (Raspbian 12.2.0-14+rpi1) 12.2.0`  
- **libmodbus version:** 3.1.11  
- **SigenStor model:** EC 12.0 TP


## 📬 Contact

For questions, suggestions, or support, feel free to contact me:
📧 software.moore@gmail.com
