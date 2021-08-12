# Smart Blind Attachment Controlled via Google Assistant

## About

This project allows for the control of a roller blind with a ball chain lift cord through the Google Assistant. The blind attachment device simply attaches to the base of the blind's lift cord to move the blinds without altering the blinds themselves - making it versatile to a wide range of blinds and renter friendly.

The project utilizes the [SinricPro Library](https://github.com/sinricpro/esp8266-esp32-sdk) to connect the device to the Google Home. SinricPro allows for the blinds to be set to any percentage position relative to the fully open position through the Google Assistant.

The device is controlled using an ESP32 Development Board. A rotary encoder is used to measure the position of the blinds and a 12V motor and motor driver is used to move the blinds up and down. A 12V AC/DC wall plug power supply powers the device. A 3D printed gear turns the lift cord and the 3D printed housing secures the components and allows for attachment to a peripheral wall.

Video demonstrating the device in action:

[![Video link demonstrating device](https://img.youtube.com/vi/RJqdqQGxrRk/0.jpg)](https://www.youtube.com/watch?v=RJqdqQGxrRk)

## Installation and Setup

### Materials

 Hardware | Software | Other
----------|----------|---------
 [ESP32 Development Board](https://www.amazon.ca/gp/product/B08HJYT6YV/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1) + Micro USB Cord | Arduino IDE | 2.4G Wifi Connection
 [Rotary Encoder](https://www.amazon.ca/gp/product/B07T3672VK/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) | SinricPro Account | 3D Printer + Materials
 [12V Motor](https://www.amazon.ca/gp/product/B07MW5NH3P/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1) | Google Account |
 [12V AC/DC Power Supply](https://leeselectronic.com/en/product/14361-14361POWERSUPPLYACDCSWITCHING12V.html) |  |
 [LM2596 Buck Converter](https://www.amazon.ca/gp/product/B08Q2YKJ6Q/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1)|  |
 [L293D H-Bridge](https://leeselectronic.com/en/product/71198-h-bridge-l293d-quadruple-half-h-driver-w-diode.html)|  |
 Breadboard and/or Prototype Board|  |
 DC Barrel Power Jack/Connector |  |
 2 x 10Ω Resistors |  |
 Header Pins|  |
 Wires|  |
 Solder & Soldering Iron |  |
 8 x M2.6 x 12 Screws |  |
 8 x M2.6 Nuts |  |
 4 x #4 3/8 Screws |  |
 2 x #8 Drywall Screws (optional for mounting) |  |

### Creating a SinricPro Device and Adding it to the Google Home

Login or create a [SinricPro](https://sinric.pro) account. Once logged in, select 'Devices' from the menu on the left. Click the '+ Add Device' button at the top to create a new device. Fill out the necessary fields in the form. Select the device type to be 'Blinds'. After this you should see a Blinds Device under your devices. It will have a device ID associated with it, we will need this later.

![SinricPro Device ID](https://user-images.githubusercontent.com/43894278/129126078-c28162f5-29e9-4dc9-85ff-3fb79744b0f9.jpeg)>

You will also need an APP KEY and APP SECRET, these can be found under 'Credentials' in the menu.

Now we need to add this new device to the Google Home. Open up the Google Home app and login or create an account. To add a new device, click the '+' in the upper left corner and select 'Set up device', search for SinricPro and log in with your account created previously. Now the blinds device should show up in your Google Home.
|                    |                        |                                |                                 |
|--------------------|------------------------|--------------------------------|---------------------------------|
| ![Add Device][Add] | ![Setup Device][Setup] | ![SinricPro Device][SinricPro] | ![Blinds Device][Blinds Device] |

[Add]:https://user-images.githubusercontent.com/43894278/129123121-1c7fbf13-0b3f-4c2b-bfda-c5d1e9050c8d.jpeg
[Setup]:https://user-images.githubusercontent.com/43894278/129123118-c7fe638c-03c7-4255-ad61-9228a8d68329.jpeg
[SinricPro]:https://user-images.githubusercontent.com/43894278/129123114-1d81cac8-5e72-4d91-b5ae-dbc3ea34b52b.jpeg
[Blinds Device]:https://user-images.githubusercontent.com/43894278/129123108-21d57ef4-c113-431b-aa01-f2a6fb04d991.jpeg

### Assembling the Circuit Board

For development I used a breadboard to ensure each component was working correctly both individually and when connected to the system. After ensuring everything worked, I proceeded to solder everything down to a prototyping board for more secure connections and to be more compact. I attached components from both sides of the prototyping board and lifted up the ESP32 board using header pins so that the space below the board could be utilized (I slipped the h-bridge into the space below). The pinouts specifications I used can be found in pinout.h and coupled with the breadboard image attached below, these pinouts can be modified but please refer to the ESP32 datasheet to see which pins are available to be used.
|                           |                                      |
|---------------------------|--------------------------------------|
| ![Breadboard][Breadboard] | ![Components w/o casing][Components] |

[Breadboard]:https://user-images.githubusercontent.com/43894278/129124386-88116fc0-2475-4e6f-8962-7667ef1d4fc5.jpg
[Components]:https://user-images.githubusercontent.com/43894278/129124280-c7530961-9761-438b-a6c2-8497b6fc0ed1.JPG

#### Modifying the Code

##### credentials.h

credentials.h will need to be updated with the information pertaining to your specific device and wifi connection. The SinricPro credentials from setting up the device on the SinricPro site are to be used here.

    // Wifi Network Credentials
    #define WIFI_SSID "YOUR-WIFI-NAME"
    #define WIFI_PASSWORD "YOUR-WIFI-PASSWORD"

    // Sinric Pro Credentials
    #define APP_KEY    "YOUR-SINRICPRO-APP-KEY"
    #define APP_SECRET "YOUR-SINRICPRO-APP-SECRET"
    #define BLINDS_ID  "YOUR-DEVICE-ID"

##### pinout.h

If you have chosen to use different pinouts on the ESP32 board, those will need to be updated in pinout.h. Here you can also modify the baud rate and speed of the motors.

The FULLY_OPEN parameter will need to be modified to cater to your specific blinds. I recommend initially setting it a low value (i.e. 50), testing how far it lifts and adjust accordingly.

You may also need to swap the MOTOR_IN_1/MOTOR_IN_2 and OUTPUT_A/OUTPUT_B pins based on how the motor and encoder is wired up.

#### Uploading the Code to the ESP32 Board

[Install Arduino ESP32 support](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-boards-manager) using the Boards Manager in the [Arduino IDE](https://www.arduino.cc/en/software).

Connect the ESP32 board via the micro USB to your computer, select the correct 'Port' for your board and select the 'Board'.
![Arduino IDE Settings](https://user-images.githubusercontent.com/43894278/129141589-c4f9dc1b-465a-45bb-80a9-1c0332b65997.png)

Open the Smart_Blinds_Automation folder in your Arduino IDE and upload to the ESP32 board.

### Printing the Parts

The 3 parts which need to be printed can be found in the "3D Print Parts" folder in the repository. You can print these STL parts however you wish.

|             Ball Chain Gear               |               Right Half of Housing             |              Left Half of Housing             |
|-------------------------------------------|-------------------------------------------------|-----------------------------------------------|
| ![Ball Chain Gear Print][Ball Chain Gear] | ![Housing Right Side Print][Housing Right Side] | ![Housing Left Side Print][Housing Left Side] |

[Ball Chain Gear]:https://user-images.githubusercontent.com/43894278/129276851-ae819818-c09c-4f16-91a0-c309d7a51a9e.png
[Housing Right Side]:https://user-images.githubusercontent.com/43894278/129276882-c094b97b-f291-41ab-890c-8283fea8f1e8.png
[Housing Left Side]:https://user-images.githubusercontent.com/43894278/129276932-3de41852-87c2-476e-9ebe-7712eba964d2.png

I designed these parts using [OnShape](https://www.onshape.com/en/). The Ball_Chain_Gear part is based from the [Bead Chain Gear](https://www.thingiverse.com/thing:38006) by [adgaudio](https://www.thingiverse.com/adgaudio/designs) and modified to attach onto the encoder and motor.

#### Resin Printing

I resin printed these parts using the [VOXELAB Polaris 3D Printer](https://www.amazon.ca/gp/product/B08FFZG73H/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) This is a lower cost resin printer and pretty beginner friendly. (Here is a [helpful video](https://www.youtube.com/watch?app=desktop&v=XSlofiAx4c0) by 'A Review From The Top' on YouTube to get started with this printer)

For these prints I used the [ANYCUBIC Clear Resin](https://www.amazon.ca/gp/product/B08NG67MMB/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1) since it was what I had on hand. You may want to use a solid coloured resin to match ur wall or blinds colour to minimize the look of the housing.

To slice my prints I used [VoxelPrint](https://www.voxelab3dp.com/download). I lifted my print off of the print bed ~8mm to allow for easier removal from the build plate when printing. Since the printer I have is rather small, I opted to slice each of my housing parts in half and print them separately. This allowed to save some wasted material on supports as well. I used VoxelPrint to auto-generate my supports (If your supports are printing but not the part itself, thicken the width of the support a bit). It took ~8 hrs to print each of the parts and I secured the two halves together by painting some resin on the connection points and quickly curing it with a UV LED nail lamp I had. ![Print Supports](https://user-images.githubusercontent.com/43894278/129143841-1812a647-f46b-4983-8997-21a7aea3984d.png)

### Assembly and Installation

|                                           |                                                           |                                                   |
|-------------------------------------------|-----------------------------------------------------------|---------------------------------------------------|
| ![Component Mounting][Component Mounting] | ![Component Mounting Beneath][Component Mounting Beneath] | ![Fully Assembled Device][Fully Assembled Device] |

[Component Mounting]:https://user-images.githubusercontent.com/43894278/129278276-876c11e0-9c07-4530-933e-0890ee077a50.JPG
[Component Mounting Beneath]:https://user-images.githubusercontent.com/43894278/129278286-e5b35b19-2e36-4f46-9218-ef14dd44472c.JPG
[Fully Assembled Device]:https://user-images.githubusercontent.com/43894278/129279991-e84d9d57-5636-4897-bd64-bbba73b362a9.jpeg


To assemble the device together, first secure the encoder and ESP32 board to the posts on left side of the housing using the M2.6 screws and nuts. Then press the header pins on the circuit board onto the ESP32 to secure the board. Feed the 12V power cable through the opening on the bottom. The ball chain gear can now be slid onto the encoder with the flat side facing in toward the encoder. The blind cord is then to be slid into the teeth of the gear and pass through the two holes located on the top of the part.

The motor is to be tucked beneath the arms on the right half of the housing and secured to the four holes using the #4 screws. Finally, place two of the nuts into the hexagonal spots left on the left side of the housing and now close the right half of the housing left half with the motor shaft inside the ball chain gear part. Align the screws in the center and secure it with two M2.6 screws. Additionally, two holes on the top and bottoms of the housing can be used to mount the device to the wall.

## Future Improvements

* Replace motor for a motor with more torque to be used on larger/heavier blinds.
* Replace motor with "embedded/attached" encoder to minimize space/decrease bulk of housing (sleeker look).
* Create and manufacture PCB board to further minimize size.
* Implement a way to setup 'FULLY_OPEN' position via hardware (button upon boot etc.)
