# Setup Instructions

## 1. Hardware Setup

1. Connect Arduino Uno to the breadboard.
2. Connect the Ultrasonic Sensor (HC-SR04) to the Arduino pins.
3. Connect the traffic signal LEDs (Red, Yellow, Green) using resistors.
4. Connect the 16x2 LCD display to the Arduino.
5. Connect the LoRa communication module to the Arduino for long-range communication.
6. Provide power supply to the Arduino board.

## 2. Software Setup

1. Install Arduino IDE on your computer.
2. Download or clone this GitHub repository.
3. Open the Arduino code file located in the `src` folder.
4. Select the correct Arduino board (Arduino Uno) in Arduino IDE.
5. Upload the code to the Arduino board.

## 3. Simulation Setup (Tinkercad)

1. Open Autodesk Tinkercad Circuits.
2. Create a new circuit project.
3. Add Arduino Uno and other required components.
4. Connect the components as shown in the circuit diagram.
5. Upload the same Arduino code.
6. Run the simulation.

## 4. Running the System

1. Power on the Arduino system.
2. When an ambulance is detected by the sensor, a signal is sent to the traffic controller.
3. The traffic signal automatically turns green for the ambulance.
4. After the ambulance passes, the signal returns to normal operation.
