/*
 * Amazon FreeRTOS MQTT Echo Demo V1.4.7
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


/**
 * @file aws_hello_world.c
 * @brief A simple MQTT double echo example.
 *
 * It creates an MQTT client that both subscribes to and publishes to the
 * same MQTT topic, as a result of which each time the MQTT client publishes
 * a message to the remote MQTT broker, the broker sends the same message back
 * to the client (the first echo).  If the MQTT client has not seen the message
 * before, it appends the string "ACK" to the message before publishing back to
 * the broker (the second echo).
 *
 * The double echo allows a complete round trip to be observed from the AWS IoT
 * console itself.  The user can subscribe to "freertos/demos/echo" topic from
 * the AWS IoT Console and when executing correctly, the user will see 12 pairs
 * of strings, one pair (two strings) every five seconds for a minute.  The first
 * string of each pair takes the form "Hello World n", where 'n' is an monotonically
 * increasing integer.  This is the string originally published by the MQTT client.
 * The second string of each pair takes the form "Hello World n ACK".  This is the
 * string published by the MQTT client after it has received the first string back
 * from the MQTT broker.  The broker also sends the second string back to the
 * client, but the client ignores messages that already contain "ACK", so the
 * back and forth stops there.
 *
 * The demo uses two tasks. The task implemented by
 * prvMQTTConnectAndPublishTask() creates the MQTT client, subscribes to the
 * broker specified by the clientcredentialMQTT_BROKER_ENDPOINT constant,
 * performs the publish operations, and cleans up all the used resources after
 * a minute of operation.  The task implemented by prvMessageEchoingTask()
 * appends "ACK" to strings received from the MQTT broker and publishes them
 * back to the broker.  Strings received from the MQTT broker are passed from
 * the MQTT callback function to prvMessageEchoingTask() over a FreeRTOS message
 * buffer.
 */

/* Standard includes. */
#include "string.h"
#include "stdio.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

/* MQTT includes. */
#include "aws_mqtt_agent.h"

/* Credentials includes. */
#include "aws_clientcredential.h"

/* Demo includes. */
#include "aws_demo_config.h"
#include "aws_hello_world.h"

/*-----------------------------------------------------------*/
/*Package Protect: BEGIN Includes*/
//Derek's includes
#include "stdint.h"
#include "stddef.h"
/*Package Protect: END Includes*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*LCD: BEGIN Functions and Global Variables*/
#define CONST_LCD_UART_REG_WRITE (0x80)
#define CONST_LCD_WIDTH 20
#define CONST_ADDR_LCD_NUM_ROWS         8
#define CONST_LCD_EMPTY 0x20
#define CONST_ADDR_LCD_DATA_START       22
#define CONST_LCD_ACTION_GO_BIT             (1 << 7)
#define CONST_ADDR_SPCL_REG             18
#define CONST_ADDR_UNLOCK1_REG          19
#define CONST_ADDR_UNLOCK2_REG          20
#define CONST_LCD_NUM_ROWS 4
#define CONST_ADDR_LCD_ACTION           21
#define CONST_SPL_FUNC_LCD_CONTRAST                 3
#define CONST_UNLOCK1 0x12
#define CONST_UNLOCK2 0x34
#define CONST_ADDR_SPCL_W_REG_1         17
#define CONST_ADDR_LCD_DATA_START       22
#define CONST_LCD_DATA_SIZE             21
#define CONST_MAX_LCD_CONTRAST 160
#define CONST_ADDR_LCD_DATA_END         (CONST_ADDR_LCD_DATA_START + CONST_LCD_DATA_SIZE)
#define CONST_LAST_REG_ADDR     CONST_ADDR_LCD_DATA_END
UART_Handle uart;
UART_Params uartParams;
unsigned char lcd_uart_tx(unsigned char *buf, unsigned char num_bytes)
{
    unsigned char x;

    for(x = 0; x < num_bytes; x++)
    {
        UART_write(uart, &buf[x], 1);
        vTaskDelay(1);
    }

    return 0;
}
unsigned char lcd_uart_write_reg(unsigned char addr, unsigned char data)
{
    unsigned char buf[2];

    //Send read request
    buf[0] = CONST_LCD_UART_REG_WRITE | addr;
    buf[1] = data;

    lcd_uart_tx(buf, 2);
    vTaskDelay(1);

    return 0;
}

//Write Register
unsigned char lcdWriteReg(unsigned char addr, unsigned char data)
{
    lcd_uart_write_reg(addr, data);
    return 0;
}

//Update the LCD
//row should be 1-4
//Data is a pointer to the data to be displayed on that particular row
//
//To clear the LCD, update each row with white space " "
inline unsigned char lcdRowWrite(unsigned char row, unsigned char *new_data)
{
    unsigned char y;
    unsigned char data_string[CONST_LCD_WIDTH+1];

    //Check row number
    if((row < 1) || (row > CONST_LCD_NUM_ROWS))
    {   return 1;
    }

//    //Check length of string
    y = strlen((char*)new_data);
    if(y > CONST_LCD_WIDTH)
    {   return 1;
    }

    //Initialize to empty
    memset(data_string, CONST_LCD_EMPTY, sizeof(data_string));

    //copy the new data
    memcpy(data_string, new_data, y);

    //Write to LCD
    for(y = 0; y < CONST_LCD_WIDTH; y++)
    { lcdWriteReg(CONST_ADDR_LCD_DATA_START + y, data_string[y]);
    }

    //Issue update command
    lcdWriteReg(CONST_ADDR_LCD_ACTION, (row-1) | CONST_LCD_ACTION_GO_BIT);

   //Wait for LCD update
    vTaskDelay(5);

    return 0;
}
//Special operations requiring an unlock sequence
unsigned char lcdSpecialFunction(unsigned char func)
{
    unsigned char x;

    x = lcdWriteReg(CONST_ADDR_SPCL_REG, func);
    x |= lcdWriteReg(CONST_ADDR_UNLOCK1_REG, CONST_UNLOCK1);
    x |= lcdWriteReg(CONST_ADDR_UNLOCK2_REG, CONST_UNLOCK2);

    //Wait a little bit
    vTaskDelay(5);
    return x;
}
//Updates the contrast, argument can be between 0 and 160
//Changes are not saved to non volatile memory
unsigned char lcdContrast(unsigned char val)
{   unsigned char y;

    y = lcdWriteReg(CONST_ADDR_SPCL_W_REG_1, val);
    y |= lcdSpecialFunction(CONST_SPL_FUNC_LCD_CONTRAST);
    return y;
}

//clear the LCD Screen
void clear_screen()
{
    unsigned char buf[CONST_LAST_REG_ADDR+1];
    unsigned char y;
    //Erase
    for(y = 0; y <= CONST_LCD_NUM_ROWS; y++)
    {   sprintf((char*) buf, " ");
        lcdRowWrite(y,buf);
    }
}
//display the ERROR screen
void display_error_screen()
{
    clear_screen();
    unsigned char buf[CONST_LAST_REG_ADDR+1];
    sprintf((char*)buf, "ERROR");
    lcdRowWrite(1,buf);
    sprintf((char*)buf, "Incorrect Pin");
    lcdRowWrite(2,buf);
}
//display "box unlocked" screen
void display_box_unlocked_screen()
{
    clear_screen();
    unsigned char buf[CONST_LAST_REG_ADDR+1];
    sprintf((char*)buf, "BOX UNLOCKED");
    lcdRowWrite(1,buf);
}
//display "enter pin" screen
void display_enter_pin_screen()
{
    clear_screen();
    unsigned char buf[CONST_LAST_REG_ADDR+1];
    sprintf((char*)buf, "ENTER PIN:");
    lcdRowWrite(1,buf);
}
/*LCD: END Functions and Global Variables*/
/*-----------------------------------------------------------*/


/**
 * @brief MQTT client ID.
 *
 * It must be unique per MQTT broker.
 */
#define echoCLIENT_ID            ( ( const uint8_t * ) "MQTTEcho" )

/**
 * @brief The topic that the MQTT client both subscribes and publishes to.
 */
#define echoTOPIC_NAME           ( ( const uint8_t * ) "freertos/demos/echo" )

/**
 * @brief The string appended to messages that are echoed back to the MQTT broker.
 *
 * It is also used to detect if a received message has already been acknowledged.
 */
#define echoACK_STRING           ( ( const char * ) " ACK" )

/**
 * @brief The length of the ACK string appended to messages that are echoed back
 * to the MQTT broker.
 */
#define echoACK_STRING_LENGTH    4

/**
 * @brief Dimension of the character array buffers used to hold data (strings in
 * this case) that is published to and received from the MQTT broker (in the cloud).
 */
#define echoMAX_DATA_LENGTH      20

/**
 * @brief A block time of 0 simply means "don't block".
 */
#define echoDONT_BLOCK           ( ( TickType_t ) 0 )

/*-----------------------------------------------------------*/
/*Package Protect: BEGIN Global Variables*/
//example: SemaphoreHandle_t xBoxOpenSem //Semaphore for controlling the lock
#define EMPTY_PIN 1
uint16_t saved_pin;
uint16_t current_pin;
uint8_t correct_pin_entered;
SemaphoreHandle_t xBoxOpenSem;
SemaphoreHandle_t xBoxDoneSem;
SemaphoreHandle_t xCollectPinSem;
SemaphoreHandle_t xPinEnteredSem;
SemaphoreHandle_t xPinCheckedSem;
SemaphoreHandle_t xBoxUnlockedScreenSem;
SemaphoreHandle_t xBoxErrorScreenSem;
SemaphoreHandle_t xDisplayNewNumberSem;
/*Package Protect: END Global Variables*/
/*-----------------------------------------------------------*/

/**
 * @brief Implements the task that connects to and then publishes messages to the
 * MQTT broker.
 *
 * Messages are published every five seconds for a minute.
 *
 * @param[in] pvParameters Parameters passed while creating the task. Unused in our
 * case.
 */
static void prvMQTTConnectAndPublishTask( void * pvParameters );

/**
 * @brief Creates an MQTT client and then connects to the MQTT broker.
 *
 * The MQTT broker end point is set by clientcredentialMQTT_BROKER_ENDPOINT.
 *
 * @return pdPASS if everything is successful, pdFAIL otherwise.
 */
static BaseType_t prvCreateClientAndConnectToBroker( void );

/**
 * @brief Publishes the next message to the echoTOPIC_NAME topic.
 *
 * This is called every five seconds to publish the next message.
 *
 * @param[in] xMessageNumber Appended to the message to make it unique.
 */
static void prvPublishNextMessage( BaseType_t xMessageNumber );

/**
 * @brief The callback registered with the MQTT client to get notified when
 * data is received from the broker.
 *
 * @param[in] pvUserData User data as supplied while registering the callback.
 * @param[in] pxCallbackParams Data received from the broker.
 *
 * @return Indicates whether or not we take the ownership of the buffer containing
 * the MQTT message. We never take the ownership and always return eMQTTFalse.
 */
static MQTTBool_t prvMQTTCallback( void * pvUserData,
                                   const MQTTPublishData_t * const pxCallbackParams );

/**
 * @brief Subscribes to the echoTOPIC_NAME topic.
 *
 * @return pdPASS if subscribe operation is successful, pdFALSE otherwise.
 */
static BaseType_t prvSubscribe( void );

/*-----------------------------------------------------------*/

/**
 * @brief The FreeRTOS message buffer that is used to send data from the callback
 * function (see prvMQTTCallback() above) to the task that echoes the data back to
 * the broker.
 */
static MessageBufferHandle_t xEchoMessageBuffer = NULL;

/**
 * @ brief The handle of the MQTT client object used by the MQTT echo demo.
 */
static MQTTAgentHandle_t xMQTTHandle = NULL;

/*-----------------------------------------------------------*/

static BaseType_t prvCreateClientAndConnectToBroker( void )
{
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn = pdFAIL;
    MQTTAgentConnectParams_t xConnectParameters =
    {
        clientcredentialMQTT_BROKER_ENDPOINT, /* The URL of the MQTT broker to connect to. */
        democonfigMQTT_AGENT_CONNECT_FLAGS,   /* Connection flags. */
        pdFALSE,                              /* Deprecated. */
        clientcredentialMQTT_BROKER_PORT,     /* Port number on which the MQTT broker is listening. Can be overridden by ALPN connection flag. */
        echoCLIENT_ID,                        /* Client Identifier of the MQTT client. It should be unique per broker. */
        0,                                    /* The length of the client Id, filled in later as not const. */
        pdFALSE,                              /* Deprecated. */
        NULL,                                 /* User data supplied to the callback. Can be NULL. */
        NULL,                                 /* Callback used to report various events. Can be NULL. */
        NULL,                                 /* Certificate used for secure connection. Can be NULL. */
        0                                     /* Size of certificate used for secure connection. */
    };

    /* Check this function has not already been executed. */
    configASSERT( xMQTTHandle == NULL );

    /* The MQTT client object must be created before it can be used.  The
     * maximum number of MQTT client objects that can exist simultaneously
     * is set by mqttconfigMAX_BROKERS. */
    xReturned = MQTT_AGENT_Create( &xMQTTHandle );

    if( xReturned == eMQTTAgentSuccess )
    {
        /* Fill in the MQTTAgentConnectParams_t member that is not const,
         * and therefore could not be set in the initializer (where
         * xConnectParameters is declared in this function). */
        xConnectParameters.usClientIdLength = ( uint16_t ) strlen( ( const char * ) echoCLIENT_ID );

        /* Connect to the broker. */
        configPRINTF( ( "MQTT echo attempting to connect to %s.\r\n", clientcredentialMQTT_BROKER_ENDPOINT ) );
        xReturned = MQTT_AGENT_Connect( xMQTTHandle,
                                        &xConnectParameters,
                                        democonfigMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT );

        if( xReturned != eMQTTAgentSuccess )
        {
            /* Could not connect, so delete the MQTT client. */
            ( void ) MQTT_AGENT_Delete( xMQTTHandle );
            configPRINTF( ( "ERROR:  MQTT echo failed to connect with error %d.\r\n", xReturned ) );
        }
        else
        {
            configPRINTF( ( "MQTT echo connected.\r\n" ) );
            xReturn = pdPASS;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

static void prvPublishNextMessage( BaseType_t xMessageNumber )
{
    MQTTAgentPublishParams_t xPublishParameters;
    MQTTAgentReturnCode_t xReturned;
    char cDataBuffer[ echoMAX_DATA_LENGTH ];

    /* Check this function is not being called before the MQTT client object has
     * been created. */
    configASSERT( xMQTTHandle != NULL );

    /* Create the message that will be published, which is of the form "Hello World n"
     * where n is a monotonically increasing number. Note that snprintf appends
     * terminating null character to the cDataBuffer. */
    ( void ) snprintf( cDataBuffer, echoMAX_DATA_LENGTH, "Hello World %d", ( int ) xMessageNumber );

    /* Setup the publish parameters. */
    memset( &( xPublishParameters ), 0x00, sizeof( xPublishParameters ) );
    xPublishParameters.pucTopic = echoTOPIC_NAME;
    xPublishParameters.pvData = cDataBuffer;
    xPublishParameters.usTopicLength = ( uint16_t ) strlen( ( const char * ) echoTOPIC_NAME );
    xPublishParameters.ulDataLength = ( uint32_t ) strlen( cDataBuffer );
    xPublishParameters.xQoS = eMQTTQoS1;

    /* Publish the message. */
    xReturned = MQTT_AGENT_Publish( xMQTTHandle,
                                    &( xPublishParameters ),
                                    democonfigMQTT_TIMEOUT );

    if( xReturned == eMQTTAgentSuccess )
    {
        configPRINTF( ( "Echo successfully published '%s'\r\n", cDataBuffer ) );
    }
    else
    {
        configPRINTF( ( "ERROR:  Echo failed to publish '%s'\r\n", cDataBuffer ) );
    }

    /* Remove compiler warnings in case configPRINTF() is not defined. */
    ( void ) xReturned;
}
/*-----------------------------------------------------------*/

static void prvMessageEchoingTask( void * pvParameters )
{
    MQTTAgentPublishParams_t xPublishParameters;
    MQTTAgentReturnCode_t xReturned;
    char cDataBuffer[ echoMAX_DATA_LENGTH + echoACK_STRING_LENGTH ];
    size_t xBytesReceived;

    /* Remove compiler warnings about unused parameters. */
    ( void ) pvParameters;

    /* Check this task has not already been created. */
    configASSERT( xMQTTHandle != NULL );
    configASSERT( xEchoMessageBuffer != NULL );

    /* Setup the publish parameters. */
    xPublishParameters.pucTopic = echoTOPIC_NAME;
    xPublishParameters.usTopicLength = ( uint16_t ) strlen( ( const char * ) echoTOPIC_NAME );
    xPublishParameters.pvData = cDataBuffer;
    xPublishParameters.xQoS = eMQTTQoS1;

    for( ; ; )
    {
        /* Each message received on the message buffer has "ACK" appended to it
         * before being published on the same topic.  Wait for the next message. */
        memset( cDataBuffer, 0x00, sizeof( cDataBuffer ) );
        xBytesReceived = xMessageBufferReceive( xEchoMessageBuffer,
                                                cDataBuffer,
                                                sizeof( cDataBuffer ),
                                                portMAX_DELAY );

        /* Ensure the ACK can be added without overflowing the buffer.
        * Note that xBytesReceived already includes null character as
        * it is written to the message buffer in the MQTT callback. */
        if( xBytesReceived <= ( sizeof( cDataBuffer ) - ( size_t ) echoACK_STRING_LENGTH ) )
        {
            /* Append ACK to the received message. Note that
             * strcat appends terminating null character to the
             * cDataBuffer. */
            strcat( cDataBuffer, echoACK_STRING );
            xPublishParameters.ulDataLength = ( uint32_t ) strlen( cDataBuffer );

            /* Publish the ACK message. */
            xReturned = MQTT_AGENT_Publish( xMQTTHandle,
                                            &xPublishParameters,
                                            democonfigMQTT_TIMEOUT );

            if( xReturned == eMQTTAgentSuccess )
            {
                configPRINTF( ( "Message returned with ACK: '%s'\r\n", cDataBuffer ) );
            }
            else
            {
                configPRINTF( ( "ERROR:  Could not return message with ACK: '%s'\r\n", cDataBuffer ) );
            }
        }
        else
        {
            /* cDataBuffer is null terminated as the terminating null
             * character was sent from the MQTT callback. */
            configPRINTF( ( "ERROR:  Buffer is not big enough to return message with ACK: '%s'\r\n", cDataBuffer ) );
        }
    }
}
/*-----------------------------------------------------------*/

static BaseType_t prvSubscribe( void )
{
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn;
    MQTTAgentSubscribeParams_t xSubscribeParams;

    /* Setup subscribe parameters to subscribe to echoTOPIC_NAME topic. */
    xSubscribeParams.pucTopic = echoTOPIC_NAME;
    xSubscribeParams.pvPublishCallbackContext = NULL;
    xSubscribeParams.pxPublishCallback = prvMQTTCallback;
    xSubscribeParams.usTopicLength = ( uint16_t ) strlen( ( const char * ) echoTOPIC_NAME );
    xSubscribeParams.xQoS = eMQTTQoS1;

    /* Subscribe to the topic. */
    xReturned = MQTT_AGENT_Subscribe( xMQTTHandle,
                                      &xSubscribeParams,
                                      democonfigMQTT_TIMEOUT );

    if( xReturned == eMQTTAgentSuccess )
    {
        configPRINTF( ( "MQTT Echo demo subscribed to %s\r\n", echoTOPIC_NAME ) );
        xReturn = pdPASS;
    }
    else
    {
        configPRINTF( ( "ERROR:  MQTT Echo demo could not subscribe to %s\r\n", echoTOPIC_NAME ) );
        xReturn = pdFAIL;
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

static MQTTBool_t prvMQTTCallback( void * pvUserData,
                                   const MQTTPublishData_t * const pxPublishParameters )
{
    char cBuffer[ echoMAX_DATA_LENGTH + echoACK_STRING_LENGTH ];
    uint32_t ulBytesToCopy = ( echoMAX_DATA_LENGTH + echoACK_STRING_LENGTH - 1 ); /* Bytes to copy initialized to ensure it
                                                                                   * fits in the buffer. One place is left
                                                                                   * for NULL terminator. */

    /* Remove warnings about the unused parameters. */
    ( void ) pvUserData;

    /* Don't expect the callback to be invoked for any other topics. */
    configASSERT( ( size_t ) ( pxPublishParameters->usTopicLength ) == strlen( ( const char * ) echoTOPIC_NAME ) );
    configASSERT( memcmp( pxPublishParameters->pucTopic, echoTOPIC_NAME, ( size_t ) ( pxPublishParameters->usTopicLength ) ) == 0 );

    /* THe ulBytesToCopy has already been initialized to ensure it does not copy
     * more bytes than will fit in the buffer.  Now check it does not copy more
     * bytes than are available. */
    if( pxPublishParameters->ulDataLength <= ulBytesToCopy )
    {
        ulBytesToCopy = pxPublishParameters->ulDataLength;

        /* Set the buffer to zero and copy the data into the buffer to ensure
         * there is a NULL terminator and the buffer can be accessed as a
         * string. */
        memset( cBuffer, 0x00, sizeof( cBuffer ) );
        memcpy( cBuffer, pxPublishParameters->pvData, ( size_t ) ulBytesToCopy );

        /* Only echo the message back if it has not already been echoed.  If the
         * data has already been echoed then it will already contain the echoACK_STRING
         * string. */
        if( strstr( cBuffer, echoACK_STRING ) == NULL )
        {
            /* The string has not been echoed before, so send it to the publish
             * task, which will then echo the data back.  Make sure to send the
             * terminating null character as well so that the received buffer in
             * EchoingTask can be printed as a C string.  THE DATA CANNOT BE ECHOED
             * BACK WITHIN THE CALLBACK AS THE CALLBACK IS EXECUTING WITHINT THE
             * CONTEXT OF THE MQTT TASK.  Calling an MQTT API function here could cause
             * a deadlock. */
            ( void ) xMessageBufferSend( xEchoMessageBuffer, cBuffer, ( size_t ) ulBytesToCopy + ( size_t ) 1, echoDONT_BLOCK );
        }
    }
    else
    {
        configPRINTF( ( "[WARN]: Dropping received message as it does not fit in the buffer.\r\n" ) );
    }

    /* The data was copied into the FreeRTOS message buffer, so the buffer
     * containing the data is no longer required.  Returning eMQTTFalse tells the
     * MQTT agent that the ownership of the buffer containing the message lies with
     * the agent and it is responsible for freeing the buffer. */
    return eMQTTFalse;
}
/*-----------------------------------------------------------*/

static void prvMQTTConnectAndPublishTask( void * pvParameters )
{
    BaseType_t xX;
    BaseType_t xReturned;
    const TickType_t xFiveSeconds = pdMS_TO_TICKS( 5000UL );
    const BaseType_t xIterationsInAMinute = 60 / 5;
    TaskHandle_t xEchoingTask = NULL;

    /* Avoid compiler warnings about unused parameters. */
    ( void ) pvParameters;

    /* Create the MQTT client object and connect it to the MQTT broker. */
    xReturned = prvCreateClientAndConnectToBroker();

    if( xReturned == pdPASS )
    {
        /* Create the task that echoes data received in the callback back to the
         * MQTT broker. */
        xReturned = xTaskCreate( prvMessageEchoingTask,               /* The function that implements the task. */
                                 "Echoing",                           /* Human readable name for the task. */
                                 democonfigMQTT_ECHO_TASK_STACK_SIZE, /* Size of the stack to allocate for the task, in words not bytes! */
                                 NULL,                                /* The task parameter is not used. */
                                 tskIDLE_PRIORITY,                    /* Runs at the lowest priority. */
                                 &( xEchoingTask ) );                 /* The handle is stored so the created task can be deleted again at the end of the demo. */

        if( xReturned != pdPASS )
        {
            /* The task could not be created because there was insufficient FreeRTOS
             * heap available to create the task's data structures and/or stack. */
            configPRINTF( ( "MQTT echoing task could not be created - out of heap space?\r\n" ) );
        }
    }
    else
    {
        configPRINTF( ( "MQTT echo test could not connect to broker.\r\n" ) );
    }

    if( xReturned == pdPASS )
    {
        configPRINTF( ( "MQTT echo test echoing task created.\r\n" ) );

        /* Subscribe to the echo topic. */
        xReturned = prvSubscribe();
    }

    if( xReturned == pdPASS )
    {
        /* MQTT client is now connected to a broker.  Publish a message
         * every five seconds until a minute has elapsed. */
        for( xX = 0; xX < xIterationsInAMinute; xX++ )
        {
            prvPublishNextMessage( xX );

            /* Five seconds delay between publishes. */
            vTaskDelay( xFiveSeconds );
        }
    }

    /* Disconnect the client. */
    ( void ) MQTT_AGENT_Disconnect( xMQTTHandle, democonfigMQTT_TIMEOUT );

    /* End the demo by deleting all created resources. */
    configPRINTF( ( "MQTT echo demo finished.\r\n" ) );
    configPRINTF( ( "----Demo finished----\r\n" ) );
    vMessageBufferDelete( xEchoMessageBuffer );
    vTaskDelete( xEchoingTask );
    vTaskDelete( NULL ); /* Delete this task. */
}
/*-----------------------------------------------------------*/
/*Package Protect: BEGIN Helper Functions*/
static int compare_pin(uint16_t pin_1, uint16_t pin_2)
{
    if (pin_1 == pin_2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static uint16_t insert_into_pin(uint16_t pin, uint16_t value)
{
    // Ensure we dont add a number if it's already four digits.
    if (pin / 10000 != 1)
    {
        pin *= 10;
        pin += value;
    }
    return pin;
}

static uint16_t remove_one_from_pin(uint16_t pin)
{
    // Ensure we don't remove if there is no pin to begin with.
    if (pin != EMPTY_PIN)
    {
        pin /= 10;
    }
    return pin;
}
/*Package Protect: END Helper Functions*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*Package Protect: BEGIN FreeRTOS Task Definitions*/
static void vOpenBoxTask(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xBoxOpenSem))
        {
            configPRINTF("Unlocking box...");
            // insert driver here to unlock
            configPRINTF("Box Unlocked.");
            xSemaphoreGive(xBoxOpenSem);
        }
        vTaskDelay(pdMS_TO_TICKS(100UL));
    }
}

static void vReadButtonPressed(void *pvParameters)
{
    while (1)
    {
        // if(GPIO polling pin == pressed)
        {
            // Add the reading of the most recent button press interrupt
            // Add driver code to read interrupt and store button value into var
            xSemaphoreGive(xButtonPressedSem);
        }
        vTaskDelay(pdMS_TO_TICKS(100UL));
    }
}

static void vKeypadTask(void *pvParameters)
{
    int8_t number_entered = 1;
    int8_t delete_button_pressed = 1;
    int8_t enter_pressed = 1;
    while (1)
    {
        xSemaphoreTake(xCollectPinSem);
        current_pin = EMPTY_PIN;
        // Add drivers to check which button was pressed
        if (number_entered)
        {
            int8_t button_value = 0;
            current_pin = insert_into_pin(current_pin, button_value);
            /*
             * If it is a number and we have less than 4, put the value in
             * a queue or other data structure. (Store int pressed,
             * update count, tell screen to type it). While we have 4 numbers,
             * ignore any future numbers pressed.
            */
           xSemaphoreGive(xDisplayNewNumberSem);
        }
        if (delete_button_pressed)
        {
            current_pin = remove_one_from_pin(current_pin);
            xSemaphoreGive(xDisplayNewNumberSem);
        }
        if (enter_pressed)
        {
            xSemaphoreGive(xPinEnteredSem);
            xSemaphoreTake(xPinCheckedSem);
            if(compare_pin(saved_pin, current_pin))
            {
                xSemaphoreGive(xBoxUnlockedScreenSem);
            }
            else
            {
                xSemaphoreGive(xBoxErrorScreenSem);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000UL));
    }
}
static void vScreenTask(void *pvParameters)
{
    // Add driver code to display "Enter Pin"
    xSemaphoreGive(xCollectPinSem);
    while (1)
    {
        if (xSemaphoreTake(xDisplayNewNumberSem))
        {
            // Add driver to show most recently entered number on screen
            xSemaphoreGive(xCollectPinSem);
        }
        if (xSemaphoreTake(xBoxErrorScreenSem))
        {
            // Add screen driver code show error screen here
            pdMS_TO_TICKS(3000UL);
            // Add screen driver code to show clear collect pin screen
            xSemaphoreGive(xCollectPinSem);
        }
        if (xSemaphoreTake(xBoxUnlockedScreenSem))
        {
            // Add driver to show box is unlocked
            pdMS_TO_TICKS(10000UL);
            xSemaphoreGive(xCollectPinSem);
        }
        vTaskDelay(pdMS_TO_TICKS(1000UL));
    }
}
static void vCheckPinTask(void *pvParameters)
{
    while (1)
    {
        if(xSemaphoreTake(xPinEnteredSem)) {
            if (compare_pin(current_pin, saved_pin))
            {
                correct_pin_entered = 1;
            }
            else
            {
                correct_pin_entered = 0;
            }
            if (correct_pin_entered)
            {
                xSemaphoreGive(xBoxOpenSem);
                xSemaphoreTake(xBoxDoneSem);
            }
            xSemaphoreGive(xPinCheckedSem);
        }
        vTaskDelay(pdMS_TO_TICKS(1000UL));
    }
}

void vTestTask (void * pvParameters ) {
    configPRINTF( ( "Entering vTestTask\n" ) );

    //Write to column 1
    GPIO_write(CC3220SF_LAUNCHXL_GPIO_COL1, 1);
    vTaskDelay(pdMS_TO_TICKS( 100UL ));
    configPRINTF( ( "1 was written to GPIO pin for Column 1\n" ) );

    //Read from row 1 10 times
    while(true)
    {
        vTaskDelay(pdMS_TO_TICKS( 1000UL ));
        if(GPIO_read(CC3220SF_LAUNCHXL_GPIO_ROW1))
        {
            configPRINTF( ( "ROW 1 returned true!\n" ) );
        }
        else
        {
            configPRINTF( ( "ROW 1 returned false!\n" ) );
        }

    }
}

void vLCDtask (void * pvParameters ) {
    configPRINTF( ( "UART_init() function called \r\n" ) );

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    //using UART1
    uart = UART_open(1, &uartParams);

    if (uart == NULL) {
        configPRINTF( ( "UART_open() function failed \r\n" ) );
        /* UART_open() failed */
        while (1);
    }

    while(1){
        //setting contrast
        lcdContrast(10);

//        lcdSpecialFunction(CONST_SPL_FUNC_CPU_RESET);//Hard Reset the LCD
        display_error_screen();
        vTaskDelay(5000);
        display_box_unlocked_screen();
        vTaskDelay(5000);
        display_enter_pin_screen();
        vTaskDelay(10000);
    }

}
/*Package Protect: END FreeRTOS Task Definitions*/
/*-----------------------------------------------------------*/

void vStartMQTTEchoDemo( void )
{
    /*-----------------------------------------------------------*/
    /*Package Protect: BEGIN Creating Semaphores*/
    xBoxOpenSem = xSemaphoreCreateBinary();
    xBoxDoneSem = xSemaphoreCreateBinary();
    xCollectPinSem = xSemaphoreCreateBinary();
    xPinEnteredSem = xSemaphoreCreateBinary();
    xPinCheckedSem = xSemaphoreCreateBinary();
    xBoxUnlockedScreenSem = xSemaphoreCreateBinary();
    xBoxErrorScreenSem = xSemaphoreCreateBinary();
    xDisplayNewNumberSem = xSemaphoreCreateBinary();
    /*Package Protect: END Creating Semaphores*/

    /*Package Protect: Initialize pin queue*/
    current_pin = EMPTY_PIN;
    saved_pin = EMPTY_PIN;
    correct_pin_entered = 0;
    /*Package Protect: END Initialize pin queue*/
    /*-----------------------------------------------------------*/

    //configPRINTF( ( "Creating MQTT Echo Task...\r\n" ) );

    /* Create the message buffer used to pass strings from the MQTT callback
     * function to the task that echoes the strings back to the broker.  The
     * message buffer will only ever have to hold one message as messages are only
     * published every 5 seconds.  The message buffer requires that there is space
     * for the message length, which is held in a size_t variable. */
    xEchoMessageBuffer = xMessageBufferCreate( ( size_t ) echoMAX_DATA_LENGTH + sizeof( size_t ) );
    configASSERT( xEchoMessageBuffer );

    /*-----------------------------------------------------------*/
    /*Package Protect: BEGIN Creating FreeRTOS Tasks*/
    configPRINTF( ( "Starting Tasks for Package Protect\r\n" ) );
    /*begin examples:
    xTaskCreate(vOpenBox, "Open Box", 512, NULL, 2, NULL); //Task for controlling the lock: Takes xBoxOpenSem whenever given. When xBoxOpenSem is taken, unlock the box.
    xTaskCreate(vKeypadCheck, "Keypad", 512, NULL, 2, NULL); //Task for checking the keypad: When correct pin is entered, gives xBoxOpenSem.
    end examples*/
    // xTaskCreate(vOpenBoxTask, "OpenBox", 512, NULL, 2, NULL);
    // xTaskCreate(vKeypadTask, "Keypad", 512, NULL, 2, NULL);
    // xTaskCreate(vScreenTask, "Screen", 512, NULL, 2, NULL);
    // xTaskCreate(vCheckPinTask, "CheckPin", 512, NULL, 2, NULL);

    xTaskCreate(vTestTask, "Task for Testing GPIO Read and Write", 512, NULL, 2, NULL);
    xTaskCreate(vLCDtask, "Task for LCD", 512, NULL, 2, NULL);

    /*Package Protect: END FreeRTOS Creating Tasks*/
    /*-----------------------------------------------------------*/


    /* Create the task that publishes messages to the MQTT broker every five
     * seconds.  This task, in turn, creates the task that echoes data received
     * from the broker back to the broker. */
    ( void ) xTaskCreate( prvMQTTConnectAndPublishTask,        /* The function that implements the demo task. */
                          "MQTTEcho",                          /* The name to assign to the task being created. */
                          democonfigMQTT_ECHO_TASK_STACK_SIZE, /* The size, in WORDS (not bytes), of the stack to allocate for the task being created. */
                          NULL,                                /* The task parameter is not being used. */
                          democonfigMQTT_ECHO_TASK_PRIORITY,   /* The priority at which the task being created will run. */
                          NULL );                              /* Not storing the task's handle. */
}
/*-----------------------------------------------------------*/
