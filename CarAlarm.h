#include "mbed.h"
#pragma once
#include <map>

#define STATE_STARTUP   0x00
#define STATE_ARMED     0x01
#define STATE_DISARMED  0x02
#define STATE_ALARM     0x03

//try this out

const float ALARM_DELAY_TIME_SECONDS = 5.0F;
const float ALARM_DURATION_IN_SECONDS = 5.0F;
const int BUTTON_HOLD_TIME_NO_ALARM_MILLISEC = 100;
const int BUTTON_HOLD_TIME_WITH_ALARM_MILLISEC = 500;
const float DISARM_TIME_MINUTES = 30.0F;
const float DEBOUNCE_TIME_SECONDS = 0.03F;

InterruptIn button(BUTTON1);
//try this

int _currentState = STATE_STARTUP;

void ChangeState(int targetState){
    if(targetState==_currentState){
            printf("Already in state %d\r\n",_currentState);
    }
    else{
        switch (targetState){
            case STATE_STARTUP:
                printf("Cannot go to startup state\r\n");
                break;
            case STATE_ARMED:
                _currentState = STATE_ARMED;
                break;
            case STATE_DISARMED:
                _currentState = STATE_DISARMED;
                break;
            case STATE_ALARM:
                _currentState = STATE_ALARM;
                break;
            default:
                printf("Behaviour undefined\r\n");
                break;
        }
    }
}

//Events
void ButtonPress(){

}

void ButtonRelease(){

}

class doorSensor{
public:
    doorSensor(PinName sensorPin) : _sensorPin(sensorPin){
        _sensorPin.rise( callback(this, doorSensor::doorOpen() ) );
        _sensorPin.fall( callback(this, doorSensor::doorClose() ) );
        if(_sensorPin.read()){
            currentDoorState = doorIsOpen;
        }else {
            currentDoorState = doorIsClosed;
        }
    } 
private:
    enum doorState {doorIsClosed, doorIsOpen};
    doorState currentDoorState;
    InterruptIn _sensorPin;

    Ticker tickerSoundAlarm;
    
    void doorOpen(){
        tickerSoundAlarm.attach(&SoundAlarm,ALARM_DELAY_TIME_SECONDS);
    }
     
    static void doorClose(){
        
    }

    static void SoundAlarm(){
        printf("Alarm is ON");
    }
    
};

InterruptIn test(BUTTON1);


class IndicatorLED {
public:
    IndicatorLED(PinName pin) : _pin(pin) {
        _pin=0;//initialise to off
    }
    void blinkFast(int ms){
        toggle();
        thread_sleep_for(ms);
        toggle();
        thread_sleep_for(ms);
    }

    void turn_on(){
        _pin.write(1);
    }

    void turn_off(){
        _pin.write(0);
    }
    
private:
    DigitalOut _pin;
    void toggle(){
        if(_pin.read()){
            _pin.write(0);
            printf("off\r\n");
        }else {
            _pin.write(1);
            printf("on\r\n");
        }
    }
};


