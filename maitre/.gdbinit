target remote :2331
monitor reset

define flash_run
  monitor reset
  load
  monitor reset
  cont
