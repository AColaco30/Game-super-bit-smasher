# Game-super-bit-smasher

## About
This game consists of getting from an 8-bit integer to another 8-bit integer, both randomly generated, using 3 bitwise operators, **AND**, **OR** or **XOR**. There are 4 LED´s that turn off as time goes by and the game ends if it expires or if the player manages to turn the initial value into the target value. The following image shows the circuit diagram:

![Circuit Diagram](res/Diagrama%20do%20circuito%20(TinkerCad).png "Circuit Diagram")

## Game
The game consists of the following steps:

- Two 8-bit random integers are generated, converted into binary and presented to the player, the target and the starting point;
- There are 3 buttons, one for each logical operation. A random number between 1 and 3 is generated, which determines whether the **AND** and/or **XOR** operations will be available. **OR** is always available and the player is notified of which operations he has;
- Then, the player must enter a decimal number. When one of the active buttons is pressed, the initial value is updated, applying the selected operator and the number entered. The new value is printed.



## License
Distributed under the MIT License. See [LICENSE](LICENSE) for more information.