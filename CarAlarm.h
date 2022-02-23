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

    enum doorState {doorIsClosed, doorIsOpen};
    doorState currentDoorState;
    int intDoorState;
   
    doorSensor(PinName sensorPin, PinName ledPin) : _sensorPin(sensorPin), _ledPin(ledPin) {//declare constructor
        _sensorPin.rise(callback(this,&doorSensor::doorOpen));//attach interrupts, rising
        _sensorPin.fall( callback(this,&doorSensor::doorClose) );//attach interrupts, falling
        if(_sensorPin.read()){
            currentDoorState = doorIsOpen;
        }else {
            currentDoorState = doorIsClosed;
        }
        _ledPin=0;
        intDoorState = 0;
    } 

    
private:
    

    InterruptIn _sensorPin;
    DigitalOut _ledPin;
    Ticker tickerSoundAlarm;

    void doorOpen(void){
        _ledPin=!_ledPin;
        if(currentDoorState == doorIsClosed) 
            {
                currentDoorState=doorIsOpen;
                intDoorState=!intDoorState;
            }
        else
            {currentDoorState = doorIsClosed;}
        //printf("door open\r\n");
        //tickerSoundAlarm.attach(&SoundAlarm,ALARM_DELAY_TIME_SECONDS);
    }

    void doorClose(void){
        //printf("door open\r\n");
    }

    static void SoundAlarm(void){
        //printf("Alarm is ON");
    }
    
};

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


class LED_toggleable {
        
    public:
        void on(void){
            _control = 1;
        };
        
        void off(void){
            _control = 0;
        };
        
        void flip(void){
            _control = !_control;
        };
        
        // Because _control and _button are private, you need to initialize them with an initializer list
        LED_toggleable(PinName button_pin, PinName output_pin) : _control(output_pin), _button(button_pin) {
            _button.fall(callback(this, &LED_toggleable::flip));
            off();
        };
 
    private:
        DigitalOut _control;
        InterruptIn _button;
};