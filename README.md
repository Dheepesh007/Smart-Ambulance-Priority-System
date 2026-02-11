# 🚑 Smart Ambulance Priority System

## 📌 Project Overview
Traffic congestion is one of the major causes of delayed emergency response. Ambulances often lose valuable time at traffic intersections, which can directly impact patient survival.

The **Smart Ambulance Priority System** is an embedded systems project designed to automatically provide traffic signal priority to ambulances approaching an intersection. The system detects the ambulance within a predefined distance and dynamically controls traffic lights to ensure safe and rapid passage. Once the ambulance clears the junction, the system restores normal traffic flow.

An **LCD display** is integrated to provide real-time system status such as ambulance detection and traffic signal changes.

---

## 🎯 Objectives
- Automatically detect an approaching ambulance  
- Provide green signal priority at traffic intersections  
- Reduce ambulance waiting time  
- Restore normal traffic signal operation after the ambulance passes  
- Minimize manual traffic control intervention  

---

## 🧠 Working Principle
The system operates using **sensor-based detection** rather than relying on siren sound, ensuring higher reliability.

1. The ambulance unit continuously monitors distance using an ultrasonic sensor.  
2. When the ambulance enters a predefined radius (**500 meters in real-world, scaled to 50 cm in simulation**), a signal is transmitted to the traffic controller.  
3. The receiver overrides the normal traffic sequence and safely transitions the lights:

RED → YELLOW → GREEN

4. After the ambulance passes the intersection:

REEN → YELLOW → RED


5. The traffic system then resumes its standard cycle.

---

## 🧪 Simulation Note
Due to Tinkercad simulator limitations, real-world distances cannot be replicated accurately. Therefore, **500 meters is scaled down to 50 cm** for simulation purposes.

This scaling is purely for demonstration and does not affect real-world implementation.

---

## 🧰 Hardware Components

### 🚑 Ambulance Unit (Transmitter)
- Arduino UNO  
- Ultrasonic Sensor (HC-SR04)  
- Slide Switch (Emergency activation simulation)  
- Jumper Wires  

### 🚦 Traffic Signal Unit (Receiver)
- Arduino UNO  
- Red, Yellow, and Green LEDs  
- 220Ω Resistors  
- Breadboard  
- **16x2 LCD Display** (for real-time status monitoring)  
- Potentiometer (LCD contrast control)  
- Jumper Wires  

---

## 💻 Software Used
- **Embedded C++** – Used to program Arduino logic and control hardware  
- **Arduino IDE** – Code development and uploading  
- **Tinkercad Circuits** – Circuit simulation  
- **GitHub** – Version control and project documentation  

---


---

## ⚙️ Algorithm

### 🔹 Transmitter Side
1. Initialize ultrasonic sensor.  
2. Continuously measure the distance.  
3. If distance ≤ threshold → send emergency signal.  
4. Else → continue monitoring.

### 🔹 Receiver Side
1. Monitor incoming signal.  
2. Upon detection:
   - Override traffic lights.  
   - Switch to priority green sequence.  
3. Wait for ambulance to pass.  
4. Restore normal traffic cycle.

---

## 🔄 Traffic Light Logic

| Condition | Signal State |
|------------|---------------|
| Normal Traffic | RED → GREEN → YELLOW |
| Ambulance Detected | RED → YELLOW → GREEN |
| Ambulance Passed | GREEN → YELLOW → RED |

---

## 🧪 Testing & Results
- The system successfully detects ambulance presence.  
- Traffic signals switch automatically without human intervention.  
- Emergency vehicles receive clear passage.  
- Normal traffic flow resumes smoothly after priority clearance.  

---

## 🚀 Applications
- Emergency vehicle priority systems  
- Smart city traffic infrastructure  
- Intelligent transportation systems  
- Ambulance and fire engine routing  

---

## 🌱 Future Enhancements
- Replace ultrasonic sensors with **GPS-based tracking**  
- Implement **RF / LoRa / GSM communication** for long-range detection  
- Develop a centralized traffic control dashboard  
- Support multiple emergency vehicles simultaneously  
- Enable real-time cloud monitoring  

---

## 📜 License
This project is developed for **academic purposes only**.

---

## ⭐ Acknowledgements
- Arduino Community  
- Autodesk Tinkercad  
- Faculty guidance and support  

---

## 👨‍💻 Author
**Kuppam Dheepesh Gupta**  
B.Tech – Engineering Student  
Alliance University
