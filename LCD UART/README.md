## CCS LCD UART Project

### Steps for setting up uartecho project
+ Go to Resource Explorer in CCS
+ Enter **CC3220SF LaunchPad** into the search bar
+ Select [**`Software/SimpleLinkCC32xxSDK/Examples/DevelopmentTools/CC3220SFLaunchPad/TIDrivers/uartecho/FreeRTOS/CCSCompiler/uartecho`**]
+ Select **Import to IDE**
+ Select the **uartecho_CC3220SF_LAUNCHXL_freertos_ccs** project in your Project Explorer and open the `uartecho.syscfg' file
+ In the **Use Hardware** dropdown, select "None" and save
+ Replace the `uartecho.c` file in the project with the version in this repo
+ If FreeRTOS error occurs when building the project: 
  + Go to Window->Preferences in CCS File Menu Bar
  + Select Code Composer Studio->Build->Variables in the left pane
  + Select **Add** and enter `FREERTOS_INSTALL_DIR` in the **Variable name**
  + In the **Type** dropdown, select **Directory**
  + Select **Browse** for the **Value** blank, and select the folder containing your version of FreeRTOS (e.g. "FreeRTOSv10.3.1")
