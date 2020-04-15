# ECEN-5813-Project5 Introduction:
This repo includes all files need to compile the files within the source code file. The main files of interest are the UART, buffer, logger files. 
The main purpose of this code is to use the KL25Z to send and receive data from a PC-based terminal program using UART communcation. This lab also included the implementation of a FMEA document that will quantify the probability of failure of certain parts of the program. The program can be run in one of three modes debug, normal mode and test mode. These modes are defined in the logger function. 

# Applications
#define Test: This program will use uUnit testing to test the functionaity of the circular buffer code. 
note: The results of this test were fail for the most of the test. This does not necessarily mean that the buffer did not work. It mean that data was not transmitted propoerly. 

#define ECHO: The echo function will send any received character back to the PC terminal. 

#Application: The application function will maintain count of every unique character receiver by the UART. 
note: though this functionality was implemented with was believed to be the proper logic it was unable to display characters and unique count for each character. 

Note: Each mode can be run with the inclusion of Interrupts or polling. 

# Observation:
1. This lab similiar to the i2c accelerometer lab was challanging an overwhelmingly long list of performance and functionality requirements. We were barely able to get through project 4 and I guess our luck had ran out here in project 5. We were able to understand the theory behind UART and circular buffers but as always the challenge came when it was time to hard code these funcations. There was little reference material to use and with the current circumstances of there being a pandemic getting help was not as ideal as person to person instruction. Because the program did not work there is alot of doubt as to if anything was learned. Maybe under different circumstances we would have been successful but alot question were left unanswered for this lab. Ultimately we choose to move forwared. 
