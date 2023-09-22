# RA6M3 and GY-521 Sensor Interface
## Introduction
This project demonstrates the interfacing of the RA6M3 microcontroller with the GY-521 sensor (MPU-6050) to acquire accelerometer, temperature, and gyroscope data. It also includes a sample application that uses user LEDs to indicate the status of an airplane model.

## Features

- **Sensor Configuration:** The RA6M3 microcontroller is configured to communicate with the GY-521 sensor using the I2C protocol. Sensor registers are configured for data acquisition.

- **Data Acquisition:** The project reads accelerometer, temperature, and gyroscope data from the GY-521 sensor.

- **Data Processing:** Raw sensor data is processed and converted into physical units for further use and the data is printed in J-Link RTT Viewer.

- **Sample Application:** A sample application is included where user LEDs are used to indicate the status of an airplane model.

## Prerequisites

- [RA6M3 Microcontroller](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ra6-series)

- [GY-521 Sensor (MPU-6050)](https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/)


## Getting Started

1. **Hardware Setup:** Connect the RA6M3 microcontroller to the GY-521 sensor.
    GY-521      RA6M3
     Vcc   -     3.3v
     Gnd   -     Gnd
     SCL   -     P512
     SDA   -     P511

3. **Software Setup:** Configure your development environment to build and flash the code onto the RA6M3 microcontroller.

4. **Compile and Flash:** Compile the project code and flash it onto the RA6M3.

5. **Run the Application:** After flashing, run the application. Observe the user LEDs for the airplane status indication and the data is printed in J-Link RTT Viewer.

## Usage

- The LEDs will indicate the status of the airplane model based on sensor data and the data is printed in J-Link RTT Viewer.
- Refer to the code for specific LED patterns and status indications.

## Contributions

Contributions to this project are welcome! Feel free to submit issues, feature requests, or pull requests.

## Acknowledgments

- Special thanks to the Renesas community and contributors for their support and resources.

---

Feel free to customize this README.md file further to include any additional details, instructions, or specific code snippets relevant to your project. Adding images, diagrams, and links can also enhance the documentation and help users understand your project better.
