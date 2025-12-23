🚑 **Smart Ambulance Priority System**
📌 **Project Overview**

Traffic congestion often delays ambulances, leading to loss of critical time and lives.
The Smart Ambulance Priority System is designed to automatically give traffic signal priority to an ambulance when it approaches an intersection with its siren ON.

This system detects the ambulance within a specified distance and dynamically controls traffic lights to allow safe and quick passage, then restores normal traffic flow.

🎯 **Objectives**

Detect an approaching ambulance automatically

Provide green signal priority at traffic intersections

Reduce ambulance waiting time

Resume normal traffic signal operation after ambulance passes

Minimize manual traffic control intervention

🧠 **Working Principle**

Ambulance siren switch turns ON the transmitter system

Ultrasonic sensor detects ambulance distance

If ambulance is within 500 meters (simulated as 50 cm in Tinkercad)

Signal is sent to traffic signal controller (receiver)

Traffic lights change sequence:

**RED → YELLOW → GREEN

After ambulance passes:

GREEN → YELLOW → RED**

Normal traffic cycle resumes

🧪 **Simulation Note** 

Due to Tinkercad simulator limitations, real-world 500 meters is scaled down to 50 cm for simulation purposes.

This scaling does not affect real-world implementation.

🧰 **Hardware Components**
Ambulance Side (Transmitter)

Arduino UNO

Ultrasonic Sensor (HC-SR04)

Slide Switch (Siren ON/OFF simulation)

Jumper Wires

Traffic Signal Side (Receiver)

Arduino UNO

Red LED

Yellow LED

Green LED

220Ω Resistors

Breadboard

💻 **Software Used**

Arduino IDE

Tinkercad Circuits (for simulation)

GitHub (version control & documentation)

📂 **Project Folder Structure**
Smart-Ambulance-Priority-System/
│
├── code/
│   ├── transmitter.ino
│   ├── receiver.ino
│
├── circuit/
│   ├── transmitter_circuit.png
│   ├── receiver_circuit.png
│
├── report/
│   ├── Project_Report.pdf
│
├── README.md

⚙️ **Algorithm**
Transmitter Side

Initialize ultrasonic sensor and siren switch

Check if siren is ON

Measure distance using ultrasonic sensor

If distance ≤ threshold → send signal

Else → no signal sent

Receiver Side

Monitor incoming signal

On signal detection:

Switch traffic lights to GREEN sequence

Wait for ambulance to pass

Restore normal traffic signal cycle

🔄 **Traffic Light Logic**
Condition	Signal State
Normal traffic	RED → GREEN → YELLOW
Ambulance detected	RED → YELLOW → GREEN
Ambulance passed	GREEN → YELLOW → RED
🧪 **Testing & Results**

System correctly detects ambulance presence

Traffic signal switches automatically

No manual intervention required

Normal traffic flow resumes successfully

🚀** Applications**

Emergency vehicle priority systems

Smart city traffic management

Ambulance and fire engine routing

Intelligent transportation systems

🌱 **Future Enhancements**

Replace ultrasonic sensor with GPS

Integrate RF / LoRa / GSM communication

Centralized traffic control dashboard

Multiple ambulance handling

Real-time cloud monitoring

📜 **License**

This project is developed for academic purposes.

⭐ **Acknowledgements**

Arduino community

Tinkercad by Autodesk

Faculty guidance and support
