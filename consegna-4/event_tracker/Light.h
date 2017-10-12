#ifndef __LIGHT__
#define __LIGHT__

/*Versione espansa dell'interfaccia proposta a lezione, presenta un metodo per invertire lo stato ed uno
per verificarlo*/

class Light {
  public:
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
    virtual int switchState() = 0;
    virtual bool isOn() = 0;
  };

#endif
