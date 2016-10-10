#ifndef RGBLED_H
#define RGBLED_H
class RGBLED
{
public:
	void lightOn(int red, int green, int blue);
	void lightOff();
  void reset();
};
#endif
