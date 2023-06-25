# BMX_OTA ESP32 Project Starter Repository

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![](https://img.shields.io/badge/PlatformIO-PIO-blue)](https://platformio.org/)
[![](https://img.shields.io/badge/ESP32-ESP32-blue)](https://www.espressif.com/en/products/socs/esp32/overview)

Welcome to the BMX_OTA ESP32 Project Starter Repository! This repository serves as a template for getting started with ESP32 development using the PlatformIO infrastructure. It provides an out-of-the-box setup for automatic WiFi connection, over-the-air (OTA) programming, and a built-in web serial interface. This allows you to quickly prototype and deploy your ESP32 projects with ease.

## Features

1. **Automatic WiFi Connection**: The BMX_OTA project starter repository simplifies the process of connecting your ESP32 device to a WiFi network. It includes a configuration file where you can specify your WiFi credentials for one or more netwroks, and the device will automatically connect on startup.

2. **Over-the-Air (OTA) Programming**: With OTA programming, you can update your ESP32 firmware wirelessly, without the need for physical access to the device. The BMX_OTA repository sets up the necessary components for OTA updates, enabling you to easily deploy new versions of your code remotely, without the need for cables.

3. **Built-in Web Interface**: The repository includes a web interface that allows you to interact with your ESP32 device through a web browser. You can send and receive data to/from the device, making it convenient for debugging and monitoring purposes.

## Prerequisites

Before getting started with the BMX_OTA ESP32 Project Starter Repository, ensure you have the following:

1. ESP32 development board: This project is specifically designed for ESP32 microcontrollers. Make sure you have a compatible ESP32 development board.

2. PlatformIO: Install PlatformIO, a powerful open-source ecosystem for IoT development. You can find installation instructions [here](https://platformio.org/install).

## Getting Started

To begin using the BMX_OTA ESP32 Project Starter Repository, follow these steps:

1. **Clone the Repository**: Clone this repository to your local machine using Git or download it as a ZIP file and extract it to a convenient location.

2. **Configure WiFi Credentials**: Rename the `include/secrets_example.h` file to `include/secrets.h` and provide your WiFi network credentials for one or several networks by replacing `<YOUR_SSID>` with your WiFi network name (SSID) and `<YOUR_PASSWORD>` with your WiFi password. Save the file.

*WARNING: If you are using a public repository, do not commit your WiFi credentials to the repository. Make sure to add the `secrets.h` file to your `.gitignore` file to prevent it from being committed.*

3. **Connect ESP32**: Connect your ESP32 development board to your computer using a USB cable. This is needed the first time you upload the code to the device. After that, you can use OTA updates to deploy new versions of your code wirelessly.

4. **Build and Upload**: Open a terminal or command prompt, navigate to the project directory, and run the following command to build and upload the code to your ESP32 device:

```shell
platformio run --target upload
```

After the first time you upload the code to the device, you can use OTA updates to deploy new versions of your code wirelessly. To do this, run the following command:

```shell
platformio run --target upload --upload-port <ESP32_IP_ADDRESS>
```

where `<ESP32_IP_ADDRESS>` is the IP address of your ESP32 device. You can find the IP address in the serial monitor after the device has connected to WiFi.

5. **Build and Upload SPIFFS**: The BMX_OTA ESP32 Project Starter Repository uses SPIFFS to store the web interface files. To upload these files to your ESP32 device, run the following command:

```shell
platformio run --target uploadfs
```
You can customize your web interface by modifying the files in the `data` directory.

For more information on uploading files to SPIFFS, see the [PlatformIO documentation](https://docs.platformio.org/en/latest/platforms/espressif32.html#uploading-files-to-file-system-spiffs).


6. **Open Serial Monitor**: After successfully uploading the code, open the serial monitor in PlatformIO to view the ESP32's output. You should see the device connecting to your WiFi network.

7. **Access the Web Serial Interface**: Once the ESP32 has connected to WiFi, open a web browser and enter the IP address shown in the serial monitor. The web serial interface will be available at "http://<IP>/webserial", allowing you to interact with the ESP32.

8. **Make your own project!**: Now that you have a working setup, you can start building your own project. You can modify the code in the `src` directory to suit your needs. You can also add new files and libraries to the project as needed.

Get started now! Just fork this repository and start building your own project!


## Contributing

If you would like to contribute to the BMX_OTA ESP32 Project Starter Repository, feel free to submit pull requests. Contributions such as bug fixes, new features, and improvements are highly appreciated.

## License

The BMX_OTA ESP32 Project Starter Repository is licensed under the [MIT License](LICENSE). Feel free to modify and adapt the codebase to suit your project's needs.

## Acknowledgements

This project was inspired by the ESP32 community and the PlatformIO development environment. We would like to express our gratitude to the open-source contributors who have made these technologies available.

---

That's it! You are now ready to kickstart your project!