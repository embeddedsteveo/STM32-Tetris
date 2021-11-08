# STM32-Tetris 
#
#
## Description
This is a little project to implement a Tetris clone on the STM32F103 based Open103V development board over the weekend. This project relies on no libraries and most of the hardware and register access is reimplemented in <stm_drivers.h> for the STM32F103VE, so beware! 

## Features

- Gamespeed is driven by TIM2 which gets faster as more points are scored
- Two channels of audio are generated for a poor rendition of the Tetris theme on DAC channels 1 and 2, driven by timers TIM4 and TIM5
- Drawing methods are optimised to not redraw the entire screen each time (reducing flickering)
- LCD is driven by the FSMC controller on the STM32F


