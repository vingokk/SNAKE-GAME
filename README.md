# SNAKE GAME - EE120B Final Project

# Intro

This is my UCR EE120B Embedded Systems final project for Fall 2019 .My project is a custom implementation of the snake game on an ATMEGA1284 Microcontroller. I have used C code and State Machine to finish the Software part based on Atmel Studio 7. Three main components are applied in my Hardware: Joystick, 8x8LED Matrix, 16x2 LCD.

# Video demo
You can see the game demo in the following video:
https://youtu.be/gDWm9CpMgJA

# Game logic
The game involves controlling a single block or snakehead by turning only left or right by ninety degrees until you manage to eat a bean. When you get the bean, the snake grows an extra block or body segment. If, or rather when, the snake  accidentally eats himself the game is over. The more beans the snake eats the higher the score will be. When the player gets enough score, he wins!

# Hardware
The LED Matrix will show the snake. The Joystick can be used to control the movement of the snake. The LCD will display the game score and other game information. 
 
**A Picture Of My Project**


**PIN Connect**

# C Code List

 * State Machine (main.c) 
 It’s the code for the state transitions and implement

 * Joystick (joystick.h)  (source site)
 It’s the code to get the input from the joystick

 * Lcd  (lcd.h &  lcd.c ) 
 It ‘s the code to generate the score information on 16x2 LCD  

 * Snake (snake.h) 
 It ‘s the code to generate the snake on 8x8 LED Matrix. 

 * Bean  (bean.h) 
 It ‘s the code to generate the bean on 8x8 LED Matrix

# Summary

 - **Challenge**

    The most difficult part in this project to represent my snake on the LED Matrix.

    I use an array to store the data of my snake’ block. In every block, there will be a Coord which includes x and y. It’s not hard to     get these data but represent on different component.  

    LED Matrix lit one led by setting line high u and column low. The problem is that you can’t lit the all leds you want at the same       time   since you will always lit the leds you don’t want.

    So how do I solve this problem?

    Actually I just lit one led everytime. At first I lit one led, then I turn it off. But from our view the led is still light. The         point   is that the light it releases will stay in human’s eyes for 4ms while atmega1284 process the code at around 1us. So there       will not be   conflict for different leds.

 - **Future**  
     I hope I can continue to finish my snake game. I plan to represent my game on LCD12864. And I ‘d like to add barriers and different      levels where the speed of snake varies. What’s more, there will be funny music sound for my game.

  # Whatever, that’s it ! 

     Bye~
     Dear Jeffrey, lovely Andre, Winston Chung Hall.
