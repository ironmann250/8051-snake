# 8051-snake
a game of snake running on an 8051 microcontroller with a led matrix as the display.

# display
https://user-images.githubusercontent.com/23479802/186889984-08f5c190-e826-493b-9488-545a02dd7a5e.mp4

# control
https://user-images.githubusercontent.com/23479802/186891293-ebada698-2fc5-4bc7-990d-601e66759daf.mp4

# circuit schematics
![8051_snake_circuit](https://user-images.githubusercontent.com/23479802/186891433-f517ec32-2e36-4d97-9f7c-35b1cd03dd38.png)

# usage
- it was written for the STC8952RC MCU but should be compatible with any 8051/2 MCUs
pay attention because it's not very optimized and i solved the memory issue, 
by shifting large variables (2 video buffers among others, this is needed because i didn't have shift registers) in other areas of the memory

- i compiled/edited in keil µvision but any ide that supports C51 is fine

- a compiled hex file of the game is provided as well

