#ifndef MODE_H_
#define MODE_H_


#define INTERRUPT
//#define ECHO
#define APPLICATION
//#define TEST
#define RESIZE_BUFFER

#define Enable_Int asm("CPSIE i");
#define Disable_Int asm("CPSID i");

#define START_CRITICAL Disable_Int
#define END_CRITICAL Enable_Int

#endif //MODE_H_
