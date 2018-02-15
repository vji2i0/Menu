#ifndef LCD
#define LCD

  void notExactTimeDelay(long timeDelay);

  void LCDSetToWrite(void);

  void LCDSetToRead(void);

  void LCDSetCommandMode(void);

  void LCDSetCharacterMode(void);

  void LCDEnableOn(void);

  void LCDEnableOff(void);

  void SetPins(void);

  void LCDSetACharacter(char character);

  void LCDSetACommand(char character);

  void LCDSetCursorPosition(int y, int x);

  void LCDSet(unsigned int phase);

  unsigned int LCDSetPeriodsToGo(unsigned int phase);


#endif
