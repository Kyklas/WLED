#pragma once

#warning "TCL59XXX Included"

#include "wled.h"

#ifndef TCL59XXX_ADDRESS
  #define TCL59XXX_ADDRESS 0x60 // or 0x30 ?
#endif

class TCL59XXX : public Usermod {

    private:

    bool     enabled;           // usermod enabled
    bool     initDone;          // status of initialisation
    bool  useTCL59xxx;

    byte tcl59xxx_pwm[17];

    //Write a byte to the IO expander
    void TCL59XXXWrite(byte address, byte *_data,size_t len) {

        int ret;

        DEBUG_PRINTF("TCL59xxx Write %d @ %02x : %02x %02x %02x %02x\n",
        len,address,_data[0],_data[1],_data[2],_data[3]);

        Wire.beginTransmission(address);
        Wire.write(_data,len);
        ret = Wire.endTransmission(); 

        DEBUG_PRINTF("TCL59xxx Xfer : %d\n",ret);
    }

    public:
    /**
     * constructor
     */
    TCL59XXX() :
    enabled(true) ,
    initDone(false),
    useTCL59xxx(true)
    {
        // todo support count ?
        memset(tcl59xxx_pwm,0,sizeof(tcl59xxx_pwm));
        tcl59xxx_pwm[0]=0x82; // set pwm register, roll over
    }


    inline uint16_t getId() { return USERMOD_ID_TCL59XXX; }

    /**
     * setup() is called once at boot. WiFi is not yet connected at this point.
     * You can use it to initialize variables, sensors or similar.
     */
    void setup()
    {
        DEBUG_PRINTLN(F("TCL59xxx : setup"));

          // if we want PCF8574 expander I2C pins need to be valid
          if (i2c_sda<0 || i2c_scl<0) useTCL59xxx = false;

          if(useTCL59xxx) {
            DEBUG_PRINTLN(F("TCL59xxx : default value"));

                
            tcl59xxx_pwm[0]=0x00;
            tcl59xxx_pwm[1]=0x0;
            TCL59XXXWrite(TCL59XXX_ADDRESS,tcl59xxx_pwm,2);

            tcl59xxx_pwm[0]=0x01;
            tcl59xxx_pwm[1]=0x00;
            TCL59XXXWrite(TCL59XXX_ADDRESS,tcl59xxx_pwm,2);

            memset(tcl59xxx_pwm+1,0xAA,4);
            tcl59xxx_pwm[0]=0x94;
            TCL59XXXWrite(TCL59XXX_ADDRESS,tcl59xxx_pwm,5);
            
            memset(tcl59xxx_pwm+1,0x0,16);
            tcl59xxx_pwm[0]=0x82;
            tcl59xxx_pwm[1]=0x20;
            TCL59XXXWrite(TCL59XXX_ADDRESS,tcl59xxx_pwm,16);

          }
    }

    /**
     * loop() is called continuously. Here you can check for events, read sensors, etc.
     */
    void loop()
    {
        yield();
        if (strip.isUpdating()) return;

        static unsigned long lastUpdate = 0;
        if (millis() - lastUpdate < 500) return;  // update only 2 times/s
        lastUpdate = millis();

        static int loop = 16;
        loop++;
        DEBUG_PRINTLN(F("TCL59xxx : value + 20"));
        tcl59xxx_pwm[1+((loop)%16)]=(loop/16*10)%256;
        tcl59xxx_pwm[1+((loop+1)%16)]=0;
        tcl59xxx_pwm[0]=0x82; // set all pwm to 20
        TCL59XXXWrite(TCL59XXX_ADDRESS,tcl59xxx_pwm,sizeof(tcl59xxx_pwm));

    }

};
