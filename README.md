# Speeduino-Simple-SD-Logger

This is Firmware for a simple SD card logger for use with the open source Speeduino ECU.

It is tested to run on an Arduino UNO with an spi card socket attached with cs on pin 4.

The connection to the Speeduino ECU is via Serial3 on the ECU itself and softserial2 port on the UNO on pins tx,5 and rx,6.

You can also monitor with a debug softserial1 port if you want on tx,2 and rx,3.

It makes a csv file that you can name in the program before you upload to the UNO else its default is SDataxx.csv where xx is the file number . A new file number is automatically allocated each time it runs and detects an old file.

This file can be uploaded to MegalogViewer from EFI Analytics for processing or and suitable csv reader.

It currently only samples every second

You will need to install the sdfat library from here https://github.com/greiman/SdFat

MOST important you must get the latest speeduino as josh has done the fix for serial3 which was broken(as of 02/02/2017 is fixed) 
