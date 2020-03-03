## How to run HelloWorld

**Prerequisites (First Time Only)**
1. *Install Code Composer Studio* (IDE) and *Install Uniflash* (TI on-chip flash). If you are using a new board, use Uniflash to *Install the Latest Service Pack*. For detailed instructions, read [set up your development environment](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_ti.html#ti-setup-env).
1. If you want monitor console output (useful for debugging), setup PuTTY.
   1. Install [putty.exe](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
   1. Create a saved session:
      1. Open PuTTY.
      1. Under *Connection type*, select *Serial*.
      1. Under *Serial line*, enter the com port used by your board, e.g. `COM11`
         + To find your com port, open your computer's Device Manager and see which UART COM port appears/disappears when you plug/unplug the board.
      1. Under *Speed*, enter `115200`.
      1. Under *Saved sessions*, enter `Package Protect`.
      1. Click *Save*.
   
1. Import the project:
   1. Clone this repo on to your computer (if needed).
   1. Open Code Composer Studio.
   1. Select *File > Open Projects from File System*.
   1. Click *Directory* and select the *AmazonFreeRTOS* folder located under *HelloWorld*. Four projects should be selected. Click *Finish*.
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
