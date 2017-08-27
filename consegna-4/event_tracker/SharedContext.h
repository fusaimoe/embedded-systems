#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__
class SharedContext {
public:
  SharedContext();
  bool isAlarm();
  void setAlarm(bool alarm);

private:
	bool alarm;
};

#endif
