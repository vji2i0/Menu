#ifndef MenuLibrary
#define MenuLibrary

  #define MENU_LAYERS 10

  char *NumberToString(int number);

  void LCDUpdate(unsigned int phase, char character, int row, int colomn);

  unsigned int LCDUpdatePeriodsToGo(unsigned int phase);

  char* MenuOption(volatile int* pointer);
  char* MenuTitle(volatile int* pointer);

#endif
