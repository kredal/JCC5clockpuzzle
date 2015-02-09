# JCC5clockpuzzle

Code by Josh Ward, for the puzzle "Spin the Throttle" as seen on JCC5.

This code is only really usable for Puzzle number 10 on JoCo Cruise 5's Puzzle Hunt, "#5isAlive".  It might also be useful
if you're making a circular array of LEDs in a switchback pattern.  The way the lights are arrayed looks something like this:

     28       3       4
       29     2     5
         30   1   6
          31  0 7 
27 26 25 24        8 9 10 11
           23 16 15
          22  17  14
        21    18    13   
      20      19      12

It would be very posible to add more lights per row, and more rows in the circle, you would just have to change all 
the %8 and %4 lines to match your new numbers.

So, wire it up like that, connect the data and clock pins to 6 and 7 (if you have a clock line), one end of a button to RST
and the other end to pin 3.
