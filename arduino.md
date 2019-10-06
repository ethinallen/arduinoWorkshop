## General Workshop Flow
- What is arduino
- How does it work
-
- Goal should be to make the light game that they made last year at cuhackit

### What is an arduino?
- It is an open source microcontroller
- #### Well what the heck is a microcontroller?
  - small computer on a single integrated circuit
  - Typically has:
      - Memory
      - Input / Output circuits

### How does it work?
- Runs a 'startup' function when it turns on
- After the initial function it will run code on a loop for as long as it is powered
  - this loop can have whatever logic you want on it! ***subject to memory constraints***

### Why is it useful?
- A full on computer (or raspberry pi) is overkill for a lot of applications
- Can make a lot of useful decisions without a lot of memory consumption

---
## Light Strip Program:
**Step 1:**
- talk about the breadboard and how it works with the arduino   

**Step 2:**   
- power the strip; change the color of lights on the strip
  - import libraries to allow the program to interface with the strip
  - teach how rgb arguments work

**Step 3:**   
- turn on a single light in the position that the programmer specifies
  - ```cpp
      #define
      for(int i = 0; )

      ```

**Step 4:**
- move the light back and forth down the strip using a for / while loop

**Step 5:**
- introduce the button and talk about how the button interacts with the program

**Step 6:**
- get the light strip to light up when the user presses the button

**Step 7**
-
