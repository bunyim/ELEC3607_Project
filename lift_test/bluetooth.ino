// connect pin 6 and 7 to 16 and 17 based on the TX and RX respectively

// reference : https://github.com/Seeed-Studio/Bluetooth_Shield_Demo_Code

//blue tooth set up function to configure it as a slave
void setupBlueToothConnection()
{
     
    blueToothSerial.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=Jamen\r\n");    // set the bluetooth name as "SeeedBTSlave"
    blueToothSerial.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    blueToothSerial.print("\r\n+STPIN=0000\r\n");
    delay(2000);                                            // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
   blueToothSerial.flush();
}


