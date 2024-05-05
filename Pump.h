#ifndef PUMP_H
#define PUMP_H

class Pump {
public:
  Pump(bool & _pumpOutput);
  void pumpOn();
  void pumpOff();
  void pumpSet(bool v);
  bool isActivated();

private:
  bool & pumpOutput;
  bool activated;
};

#endif
