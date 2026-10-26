# RC Smart Car (ESP32)

A remote-controlled car built around an **ESP32** controller. You drive it from your phone over **Bluetooth**, and it protects itself with a **crash avoidance system** that keeps it from hitting obstacles.

## Features

- **Bluetooth control:** drive the car from your phone (forward, backward, left, right, stop).
- **Crash avoidance:** a distance sensor checks the way ahead, and the car reacts before it hits an obstacle.
- **ESP32 brain:** one board handles Bluetooth, sensor reading, and motor control.

## How it works

1. The phone connects to the ESP32 over Bluetooth and sends one command at a time.
2. The ESP32 reads each command and drives the motors.
3. At the same time, the ESP32 reads the distance sensor.
4. If an obstacle gets too close, the crash avoidance takes priority over the driver's command and the car reacts to avoid the crash.
5. When the way is clear again, the car follows the driver's commands as normal.

```
Phone --Bluetooth--> ESP32 --> Motors
                       ^
              Distance sensor (obstacle check)
```

## Components

- ESP32 controller
- Distance sensor
- DC motors and motor driver
- Battery
- Chassis and wheels

## Getting started

1. Download or clone this repository.
2. Upload the code to the ESP32 board.
3. Power the car.
4. Pair your phone with the car over Bluetooth.
5. Send commands from your phone to drive.

## Future improvements

- Add speed control from the phone.
- Add more sensors (left and right) for smarter steering.
- Add an autonomous driving mode.

## Author

**Caroline Noshy Thabet**, Computer Science student at Assiut University.
GitHub: [Carolin-Noshy](https://github.com/Carolin-Noshy)
