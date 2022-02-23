#include "mbed.h"
#include "platform/mbed_thread.h"
#include <map>
#include "CarAlarm.h"





int main(){
    printf("Hellooooo World!\r\n");
    
    doorSensor door(BUTTON1,LED1);
    while(true) {
        printf("%d\r\n",door.intDoorState);
        thread_sleep_for(500);
        //disp.blinkFast(200);
    }
}