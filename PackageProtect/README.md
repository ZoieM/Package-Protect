## Pins Used
Read [PackageProtect/AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.c](https://github.com/ZoieM/Package-Protect/blob/master/PackageProtect/AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.c)
and [PackageProtect/AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.h](https://github.com/ZoieM/Package-Protect/blob/master/PackageProtect/AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.h)
for pin details.

To see where the pins are on your board, look at the [Pinout Guide](http://www.ti.com/lit/ug/swau124/swau124.pdf).

### GPIO Pins
+ LOCK
    + Name: *CC3220SF_LAUNCHXL_GPIO_LOCK* 
    + Info:`GPIOCC32XX_GPIO_11 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW`

+ DETECT KEYPAD PRESS
    + Name: *CC3220SF_LAUNCHXL_GPIO_KEYPAD_PRESSED*
    + Info: `GPIOCC32XX_GPIO_22 | GPIO_CFG_INPUT | GPIO_CFG_IN_INT_RISING`

+ KEYPAD
   + KEYPAD COLUMN 1
       + Name: *CC3220SF_LAUNCHXL_GPIO_COL1*
       + Info: `GPIOCC32XX_GPIO_12 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW`
   + KEYPAD COLUMN 2
       + Name: *CC3220SF_LAUNCHXL_GPIO_COL2*
       + Info: `GPIOCC32XX_GPIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW`
   + KEYPAD COLUMN 3
       + Name: *CC3220SF_LAUNCHXL_GPIO_COL3*
       + Info: `GPIOCC32XX_GPIO_14 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW`
   + KEYPAD COLUMN 4
       + Name: *CC3220SF_LAUNCHXL_GPIO_COL4*
       + Info: `GPIOCC32XX_GPIO_28 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW`   
   + KEYPAD ROW 1
       + Name: *CC3220SF_LAUNCHXL_GPIO_ROW1*
       + Info: `GPIOCC32XX_GPIO_13 | GPIO_CFG_INPUT | GPIO_CFG_IN_INT_RISING`         
   + KEYPAD ROW 2
       + Name: *CC3220SF_LAUNCHXL_GPIO_ROW2*
       + Info: `GPIOCC32XX_GPIO_05 | GPIO_CFG_INPUT | GPIO_CFG_IN_INT_RISING`
   + KEYPAD ROW 3
       + Name: *CC3220SF_LAUNCHXL_GPIO_ROW3*
       + Info: `GPIOCC32XX_GPIO_03 | GPIO_CFG_INPUT | GPIO_CFG_IN_INT_RISING`
   + KEYPAD ROW 4
       + Name: *CC3220SF_LAUNCHXL_GPIO_ROW4*
       + Info: `GPIOCC32XX_GPIO_04 | GPIO_CFG_INPUT | GPIO_CFG_IN_INT_RISING`
   + KEYPAD ROW 5
       + Name: *CC3220SF_LAUNCHXL_GPIO_ROW5*
       + Info: `GPIOCC32XX_GPIO_23 | GPIO_CFG_INPUT | GPIO_CFG_IN_INT_RISING`     
 
 ### UART Pins
 + TX GPIO_07 (pin 62). Code still in progress.

## How to run PackageProtect

If you have already followed the [HelloWorld Instructions](https://github.com/ZoieM/Package-Protect/tree/master/HelloWorld) to set yur development environment and the console output monitor, you only need to import this project and run it: 


**Prerequisites (First Time Only)**
1. Import the project:
   1. Clone this repo on to your computer (if needed).
   1. Open Code Composer Studio.
   1. Select *File > Open Projects from File System*.
   1. Click *Directory* and select the *AmazonFreeRTOS* folder located under *PackageProtect*. Four projects should be selected. Click *Finish*.
1. Configuring the project:
   1. Double-click *aws_demos* to make it the active project.
   1. To configure WiFi, modify *AmazonFreeRTOS/demos/common/include/aws_clientcredential.h*.
      1. Set `#define clientcredentialWIFI_SSID` to the *name of the WiFi network* that you want to use the board with.
         + Using your phone as a hotspot might be easiest--otherwise you will need to change the WiFi settings between home/school/elsewhere.
         + If you are on campus you cannot use SJSU_premier nor eduroam; you must use the SJSU_MyDevice WiFi network.
         + Special characters might cause problems. Repeated WiFi names (e.g. two "default" WiFis in the same area) might cause problems.
      1. Set `#define clientcredentialWIFI_PASSWORD` to the *password* of the WiFi network that you want to use the board with. 
         + If you are on campus using SJSU_MyDevice, the password is an empty string ("").
      1. Set `#define clientcredentialWIFI_SECURITY` to the *security type* of the WiFi network you are using.
         + Typically use `eWiFiSecurityWPA2`.
         + With SJSU_MyDevice, use `eWiFiSecurityOpen`.

**Running the demo (Every Time)**
1. Double-click *aws_demos* to make it the active project.
1. *Build* the project.
1. *Run* the project:
   1. Make sure the board is plugged into your computer. If needed, move the SOP jumper to 0 and click the reset button.
   1. Click *Debug*.
   1. If you want to monitor console output:
      1. Open PuTTY.
      1. Double-click `Package Protect`. 
   1. If you want to monitor the MQTT messages:
      1. Open the [AWS MQTT Client](https://us-west-2.console.aws.amazon.com/iot/home?region=us-west-2#/test) (username: `zoiemacdougall@gmail.com` password: `PackageProtect2020`)
      1. Under *Subscription topic*, enter `freertos/demos/echo` and click *Subscribe*.
   1. If you are using your phone as a hotspot, open that screen now.
   1. Click *Resume*.


## Other references

For comprehensive instructions on running this demo, refer to the [CC3220SF-LAUNCHXL Getting Started Guide](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_ti.html) and the [Getting Started section of Amazon FreeRTOS webpage](https://aws.amazon.com/freertos).

For detailed documentation on Amazon FreeRTOS, refer to the [Amazon FreeRTOS User Guide](https://aws.amazon.com/documentation/freertos).

To evaluate Amazon FreeRTOS without using MCU-based hardware, you can use the Windows Simulator.
* Requirements: Microsoft Windows 7 or newer, with at least a dual core and a hard-wired Ethernet connection
* [Getting Started Guide](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_windows.html)
* IDE: [Visual Studio Community Edition](https://www.visualstudio.com/downloads/)
