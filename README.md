# SimpleIrBlaster

Use this code to build an Arduino device that can send IR device commands from your PC. Commands are sent the serial port. To assist with that, consider using https://github.com/p-elsie/ttyUtil , and consider EventGhost too. 

Usage:

  type address command repeats

  The above input, should be four integer values, delimited with a space or comma character.

  These are the supported types:

    1 NEC
    2 Samsung
    3 Sony
    4 Panasonic
    5 RC5
    6 RC6
    7 Sharp
    8 LG
    9 JVC
    10 Onkyo
    11 Apple

IRDB code reference: https://github.com/probonopd/irdb
