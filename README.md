# Autonomous Mobile Robotics - Bluetooth Control Branch

This branch contains the modified codebase to control the Mecanum wheel robot strictly via an **HC-05 Bluetooth Module**. It also includes a modern, web-browser-based **XAMPP UI Controller**.

## Features
- Complete control over all robot vectors (Forward, Backward, Left, Right, Strafe Left, Strafe Right).
- Full actuator control over the forklift (Up/Down) and the clamp (Open/Close).
- A mobile-friendly Dashboard UI hosted via XAMPP over your local WiFi.

## 1. Hardware Setup (Arduino MEGA)
1. **Bluetooth Module**: Connect your HC-05 module to the Arduino MEGA's `Serial1`.
   - HC-05 **TX** -> Arduino **RX1** (Pin 19)
   - HC-05 **RX** -> Arduino **TX1** (Pin 18)

## 2. Setting up the XAMPP Web Controller
The web controller allows you to use your smartphone as a steering/action dashboard.
1. Copy the `XAMPP_UI_Controller` folder into your XAMPP installation directory: `C:\xampp\htdocs\`
2. Turn on your PC's Bluetooth and pair it with the **HC-05** module.
3. Once paired, go to your Windows Bluetooth Settings -> More Bluetooth Options -> COM Ports.
4. Locate the Outgoing COM port assigned to the HC-05 (e.g., `COM4` or `COM5`).
5. Open Command Prompt and type `ipconfig` to find your PC's IPv4 address (e.g., `192.168.1.15`).

## 3. Remote Controlling
1. Start XAMPP (Apache).
2. Ensure your smartphone is connected to the **same WiFi network** as your PC.
3. On your phone's browser, go to `http://<YOUR_PC_IP>/XAMPP_UI_Controller/`
4. Type the COM port you found earlier into the bottom Configuration panel and tap **Save**.
5. You can now use the on-screen D-Pad and Actuator buttons to drive the robot!
