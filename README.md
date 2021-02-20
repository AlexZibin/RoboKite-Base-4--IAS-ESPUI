# RoboKite-Base-4--IAS-ESPUI

This is my brief attempt to combine (in one sketch) two must-have libraries:
  1) https://github.com/iotappstory/ESP-Library
  2) https://github.com/s00500/ESPUI
  
Unfortunately sketch crashes when I press the Update button
(which calls IAS.callHome () in line 58 of espui1.cpp) 
with the following dump:
```Button DOWN
Button UP
 Calling Home

 Checking for App(Sketch) updates from: https://iotappstory.com/ota/updates
 No updates necessary!

 Checking for SPIFFS updates from: https://iotappstory.com/ota/updates
E (62502) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (62502) task_wdt:  - async_tcp (CPU 0/1)
E (62502) task_wdt: Tasks currently running:
E (62502) task_wdt: CPU 0: IDLE0
E (62502) task_wdt: CPU 1: async_tcp
E (62502) task_wdt: Aborting.
abort() was called at PC 0x400ded4b on core 0

Backtrace: 0x4008c454:0x3ffbe170 0x4008c685:0x3ffbe190 0x400ded4b:0x3ffbe1b0 0x40084771:0x3ffbe1d0 0x401a69cb:0x3ffbc450 0x400e0102:0x3ffbc470 0x4008a381:0x3ffbc490 0x40088b9d:0x3ffbc4b0

Rebooting...
```
