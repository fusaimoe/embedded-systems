#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__

class SharedContext {
public:
  SharedContext();

  bool isOn();
  void setOn(bool on);
  bool isPark();
  void setPark(bool park);

  bool isStopped();
  void setStopped(bool stopped);
  bool isMoving();
  void setMoving(bool moving);
  bool isContact();
  void setContact(bool contact);
  bool isDanger();
  void setDanger(bool danger);
  int getAttack();
  void setAttack(int attack);

private:
  bool on;
  bool park;

  bool stopped;
  bool moving;
  bool contact;
  bool danger;
  int attack;
};

#endif
