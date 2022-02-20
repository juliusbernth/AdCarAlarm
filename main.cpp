#include "mbed.h"
#include "platform/mbed_thread.h"
#include <map>
#include "CarAlarm.h"





int main(){
    printf("Hellooooo World!\r\n");
    IndicatorLED disp(LED1);
    while(true) {
        disp.blinkFast(200);
    }
}