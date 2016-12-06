#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__

class SharedContext {
public:
  SharedContext();
  bool isStopped();
  void setStopped(bool stopped);
  bool isMoving();
  void setMoving(bool moving);
  bool isContact();
  void setContact(bool contact);
  bool isDanger();
  void setDanger(bool danger);
  int getAttack();
  void resetAttack();

private:
  bool stopped;
  bool moving;
  bool contact;
  bool danger;
  int attack;
};

#endif
