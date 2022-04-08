[![arduino-library-badge](https://www.ardu-badge.com/badge/OV5640%20Auto%20Focus%20for%20ESP32%20Camera.svg)](https://www.ardu-badge.com/OV5640%20Auto%20Focus%20for%20ESP32%20Camera)

# Enable OV5640's autofocus function on ESP32 AI-THINKER Board

This library contains the necessary firmware and source code to enable the OV5640 autofocus mode on the ESP32.

## Note
Each manufacturer of OV5640 has slightly different specifications. Please check with your product first. The product I used is Waveshare's OV5640. https://www.waveshare.com/wiki/OV5640_Camera_Board_(C)

## Installation

### ESP32 Core Library
You need to install the ESP32 core libraries.
The install instructions for your specific OS are here:
https://github.com/espressif/arduino-esp32

### Using Arduino Library Manager

From Arduino IDE, go to menu *Sketch -> Include Library -> Manage Libraries...*
In Library Manager Window, search *"OV5640"* in the search form then select *"OV5640 Auto Focus for ESP32 Camera"*
Click *"Install"* button.

### Manual installation

Download zip file from this repository by selecting the green *"Code"* dropdown at the top of repository, select *"Download ZIP"*
From Arduino IDE, select menu *Sketch -> Include Library -> Add .ZIP Library...*

Or use git:
 ```
 cd ~/arduino/libraries/
 git clone git@github.com:0015/ESP32-OV5640-AF.git
 ```

Then you should see the examples and be able to include the library in your projects with:

```
 #include "ESP32_OV5640_AF.h"
```

## Usage

This works like a standard Arduino library. Here's a minimal example:

```
// Create an object from OV5640 class at the top of your sketch
OV5640 ov5640 = OV5640();

// To start OV5640, neet to pass the pointer of the esp camera sensor
sensor_t* sensor = esp_camera_sensor_get();
ov5640.start(sensor);

// Download Firmware for AF
if (ov5640.focusInit() == 0) {
 Serial.println("OV5640_Focus_Init Successful!");
}

// Set Continuous AF MODE
if (ov5640.autoFocusMode() == 0) {
 Serial.println("OV5640_Auto_Focus Successful!");
}
```

See the OV5640_Console_Test example for a more fully-featured example.

## Hardware Modification

To use the AF function of the OV5640 on the ESP32 AI-Thinker board, you need to connect 3.3v to the last 24th pin(AF-VCC).
I share what I've been working on. [You can also see how AF works.](https://youtu.be/922BWy3OOoQ)

<a href="https://youtu.be/922BWy3OOoQ">
<img width="800" src="https://github.com/0015/ESP32-OV5640-AF/blob/main/misc/main.jpg">
</a>

# Updates 

 - v0.1.1
    - Only Added CONTINUOUS AUTOFOCUS Mode

# License

 This software is written by Eric Nam and is licensed under The MIT License. Check License file for more information.    