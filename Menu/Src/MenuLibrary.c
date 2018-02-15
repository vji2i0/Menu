#include "LCD.h"
#include "MenuLibrary.h"
#include <stdio.h>



  char *NumberToString(int number)
  {
    static char snumber[6];
    if (number<10)
    {
      sprintf(snumber, "    %d", number);
    }else if (number<100){
      sprintf(snumber, "   %d", number);
    }else if (number<1000){
      sprintf(snumber, "  %d", number);
    }else if (number<10000){
      sprintf(snumber, " %d", number);
    }else if (number<100000){
      sprintf(snumber, "%d", number);
    }
    return snumber;
  }


  void LCDUpdate(unsigned int phase, char character, int row, int colomn)
  {
    switch (phase)
    {
      case 1:
      {
        LCDSetToWrite();
        LCDSetCommandMode();
        break;
      }
      case 2:
      {
        LCDEnableOn();
        break;
      }
      case 3:
      {
        LCDSetCursorPosition(row, colomn);
        break;
      }
      case 4:
      {
        LCDEnableOff();
        break;
      }
      case 5:
      {
        LCDSetToWrite();
        LCDSetCharacterMode();
        break;
      }
      case 6:
      {
        LCDEnableOn();
        break;
      }
      case 7:
      {
        LCDSetACharacter(character);
        break;
      }
      case 8:
      {
        LCDEnableOff();
        break;
      }
    }
  }

  unsigned int LCDUpdatePeriodsToGo(unsigned int phase)
  {
    volatile int j=0;
    switch (phase)
    {
      case 1:
      {
        j=0;
        break;
      }
      case 2:
      {
        j=0;
        break;
      }
      case 3:
      {
        j=0;
        break;
      }
      case 4:
      {
        j=9;
        break;
      }
      case 5:
      {
        j=0;
        break;
      }
      case 6:
      {
        j=0;
        break;
      }
      case 7:
      {
        j=0;
        break;
      }
      case 8:
      {
        j=9;
        break;
      }
     }
    return j;
  }


char* MenuOption(volatile int* pointer)
{
  static char str[16];
  sprintf(str, "                ");
  switch (pointer[0])
  {
    case 1:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str," Print          ");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 1         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 2         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 3         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 4         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 5         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 2:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str, " Settings       ");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Type of plastic");
              //sprintf(str,"____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " ABS plastic    ");
                  //sprintf(str,"TYPE OF PLASTIC_");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                sprintf(str, " PLA plastic    ");
                //sprintf(str,"TYPE OF PLASTIC_");
                break;
              }
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Extruder temp. ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Calibrate      ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " Yes, do it     ");
                  //sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " No, don't do it");
                  //sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Brightness     ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Language       ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " English        ");
                  //sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " Russian        ");
                  //sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 3:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str, " Change filament");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
    case 4:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str, " Help           ");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
  }
  return str;
}


char* MenuTitle(volatile int* pointer)
{
  static char str[16];
  sprintf(str, "                ");
  switch (pointer[0])
  {
    case 1:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str," Print          ");
          sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 1         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 2         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 3         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 4         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 5         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 2:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str, " Settings       ");
          sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Type of plastic");
              sprintf(str,"____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " ABS plastic    ");
                  sprintf(str,"TYPE OF PLASTIC_");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                //sprintf(str, " PLA plastic    ");
                sprintf(str,"TYPE OF PLASTIC_");
                break;
              }
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Extruder temp. ");
              sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Calibrate      ");
              sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " Yes, do it     ");
                  sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " No, don't do it");
                  sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Brightness     ");
              sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Language       ");
              sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " English        ");
                  sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " Russian        ");
                  sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 3:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str, " Change filament");
          sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
    case 4:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str, " Help           ");
          sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
  }
  return str;
}
