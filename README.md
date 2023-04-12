# SmartMouseTrap

This is Arduino code for 2 Arduinos running to create the Smart Mouse Trap.

Arduino #1 must have an UltraSonic Sensor and motor.
Arduino #2 must have 2 LEDs and a button.
Both Arduinos should be connected via UART communication system.

The code for Arduino #1 handles the logic for detecting a distance less than 5 cm, then closes the trap and sends a signal to Arduino #2. In this state, the arduino is effectively frozen until a signal is recieved from Arduino #2. When the signal is recieved, the door will open and the arduino will be unfrozen and resume the logic. 

The code for Arduino #2 initally turns the first (red) LED on. Apon recieving a signal from Ardunio #1, the first (red) LED will turn off and the second (green) LED will turn on. At this point, when the button is pressed, the LEDs will switch states again and a signal is sent to Arduino #1.
