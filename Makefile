# File:   Makefile
# Author: C. Papple, K. Lai
# Date:   20 Oct 2021
# Descr:  Makefile for blinky

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: blinky.out


blinky.o: blinky.c ../../drivers/avr/system.h  ../../utils/task.h 
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@
	
navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@
	
ledmat.o: ../../drivers/ledmat.c ../../drivers/ledmat.h ../../drivers/test/avrtest.h ../../drivers/test/pio.h ../../drivers/test/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/test/system.h ../../drivers/test/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h
	$(CC) -c $(CFLAGS) $< -o $@

task.o: ../../utils/task.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/task.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@
	
player-loc.o: player_loc.c player_loc.h ../../drivers/navswitch.c ../../drivers/ledmat.h ../../drivers/test/system.h
	$(CC) -c $(CFLAGS) $< -o $@

obstacle.o: obstacle.c obstacle.h level_select.h ../../drivers/display.h ../../drivers/ledmat.h ../../drivers/test/system.h
	$(CC) -c $(CFLAGS) $< -o $@

level-select.o: level_select.c level_select.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@
	
blinky_tasks.o: blinky_tasks.c blinky_tasks.h player_loc.h obstacle.h level_select.h ../../drivers/avr/system.h ../../drivers/navswitch.h ../../drivers/ledmat.h ../../utils/pacer.h ../../utils/task.h ../../utils/uint8toa.h
	$(CC) -c $(CFLAGS) $< -o $@

uint8toa.o: ../../utils/uint8toa.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
blinky.out: blinky.o system.o navswitch.o ledmat.o pacer.o timer.o display.o task.o tinygl.o font.o player-loc.o obstacle.o level-select.o uint8toa.o blinky_tasks.o timer.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@




# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: blinky.out
	$(OBJCOPY) -O ihex blinky.out blinky.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash blinky.hex; dfu-programmer atmega32u2 start

