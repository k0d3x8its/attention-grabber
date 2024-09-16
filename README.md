# Attention-Grabber

## Overview

This project creates an attention-grabbing notification system using a Feather Huzzah ESP8266 and a NeoPixel Featherwing. The system includes a physical button and a virtual button that can be accessed via a static IP address. When the virtual button is pressed, it triggers the LEDs on the NeoPixel Featherwing to blink in bright red, designed to catch the attention of individuals in the vicinity.

### Scenario

Imagine kids playing video games in one room while parents are in another room and want to get their attention without yelling or leaving their seat. This system provides a convenient solution by using blinking LEDs to signal the kids, making it an effective communication tool in such scenarios.

## BUIDL of Materials

1. **Feather Huzzah ESP8266**
   - A compact Wi-Fi microcontroller board used to control the NeoPixel LEDs and host the web server for the virtual button.

2. **NeoPixel Featherwing**
   - A 32-pixel LED strip that lights up in red when triggered. It is mounted on the Featherwing and connected to the Feather Huzzah.

3. **Featherwing Doubler**
   - An accessory board used to connect both the Feather Huzzah and the NeoPixel Featherwing.

4. **Physical Push Button**
   - A button that can be connected to the Feather Huzzah to trigger the LED blinking through the virtual button interface.

5. **Power Supply**
   - A suitable power source to power the Feather Huzzah and NeoPixel Featherwing.

## Documentation

### Hardware Setup

1. **Connect the NeoPixel Featherwing to the Feather Huzzah**:
   - Use the Featherwing Doubler to connect the NeoPixel Featherwing to the Feather Huzzah. Ensure the connections are secure.

2. **Wire the Physical Button**:
   - Connect one terminal of the physical button to a GPIO pin on the Feather Huzzah (for example, GPIO12). Connect the other terminal to the ground (GND). (*coming soon*)

3. **Power the System**:
   - Connect a suitable power supply to the Feather Huzzah to power both the Feather Huzzah and the NeoPixel Featherwing. This can be 5V via USB or 3.3V via the JST connector.

### Software Setup

1. **Upload the Code to the Feather Huzzah**:
   - Use the Arduino IDE to upload the provided code to the Feather Huzzah. Ensure the correct board and port are selected.

2. **Access the Virtual Button**:
   - After uploading the code, open the Serial Monitor in the Arduino IDE to find the IP address assigned to the Feather Huzzah.
   - Enter this IP address in a web browser to access the virtual button interface.

### Usage

1. **Physical Button**:
   - Pressing the physical button will activate the LEDs to blink, simulating the action of the virtual button for testing purposes.

2. **Virtual Button**:
   - Visit the static IP address provided by the Feather Huzzah in a web browser.
   - Press the "Toggle LED" button on the web interface to make the NeoPixels turn on. The LEDs will stay on until the button is pressed again.

---

Feel free to adjust the IP address, button functionality, and other parameters as needed for your specific setup and requirements.
