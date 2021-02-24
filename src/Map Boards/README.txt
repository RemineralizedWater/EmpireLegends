__________________________________________________________
**** This file demonstrates the format for a map file ****
__________________________________________________________

continent|territory|adjacency

continent
    ex. 1,2,3,4,5,6 ...

territory
    ex. 1,2,3,4,5,6 ...

adjacency
    each adjacent territory is separated in brackets along with its route type such as Water or Land
    (L or W, territory)
    L--> Land
    W--> Water

    ex.  (L,8)
    territory is adjacent to territory 8 via Land

ex.
1|8|(L,9)(W,10)

continent --> 1
territory --> 8
adjacency -->
    1. between current territory 8 and territory 9 by Land
    2. between current territory 8 and territory 10 by Water


Note: Each of the map board pieces are separated by '-'

_____________________________________________________________
                   ****** Invalid Maps Files *******
_____________________________________________________________
Used for testing purposes

invalid1_map.txt - does not follow map format
    - error at line 1

invalid2_map.txt - terrs that belong to multiple continents
    - error at lines 7-10

invalid3_map.txt - terrs that are not connected
    - error at lines 22-23
