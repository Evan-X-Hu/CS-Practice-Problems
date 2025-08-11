INPUT: a string consisting of all the present atoms, either H's or O's
Will be a multiple of 3 and have a ratio of 1:2 - O:H

OUTPUT: a string will all sets of water

RULES:
1. If an oxygen arrives and no hydrogen are present, it must wait for 2 hydrogen atoms

2. If a hydrogen arrives and no oxygen are present, it must wait for 1 oxygen

3. The order of the pairing doesn't matter (IE: the water molecules are sets)

SOLUTION:

First we must have locks for accepting Oxygen and Hydrogen. We can use a counter for each. Use counting conditional variables for both and have Oxygen initialize and reinitialize to 1 while Hydrogen is 2.
WE NEED A SHARED LOCK SINCE WE ARE WAITING ON 2 THREAD'S CONDITIONS.
The lock wil be unlocked when we are waiting on the group of (O, H, H)
The lock will be locked when

In each release method. We must check if the lock is open, if it is we must output our atom and then release the lock (or maybe release then output, im unsure)