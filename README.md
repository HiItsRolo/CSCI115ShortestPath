# CSCI115ShortestPath
Project for class using dijkstra shortest path algorithm and midpoint algorithm for terrain generation.

========================================================================================================

TERRAIN GENERATION
-In Main.cpp

-Midpoint Algorithm will generate terrain for an (N^2)+1 size grid. (i.e 5x5, 10x10)

-Using %120 and a range for values for each element that will be placed on the map,
a map will be randomly created and saved to a text file "terrain.txt"

Key guide for elements:
"O" = Ocean
"B" = Beach
"D" = Desert
"F" = Forest
"P" = Plain
"H" = Foothills
"M" = Middle Mountain
"T" = High Mountain

-terrain.txt file may have more elements than what desired grid may hold.
values will be taken starting from top left corner and proceed down and right.
(e.g top-left corner will be (0,gridsize-1).

-Initialized by calling M->generateTerrain() in main.cpp;


---------------------------------------------------------------------------------------------------------
COST MATRICES FOR EDGES

Cost Matrix for Human

MAX = inaccessable to character

From/to High mountain Middle mountain Foothills Plain Forest Desert Beach Ocean
High
Mountain  	MAX 	MAX 		MAX 	MAX 	MAX 	MAX   NAX  MAX
Middle
Mountain  	MAX 	4 		5 	6 	8 	9     15   MAX
Foothills 	MAX	2 		2 	3 	3 	2     15   MAX
Plain 	 	MAX	3 		3 	1 	1 	2     3    MAX
Forest   	MAX 	4 		4 	2 	2 	2     7    MAX
Desert   	MAX 	5 		2 	2 	1	2     4	   MAX
Beach     	MAX 	5 		3 	2 	3 	1     2    MAX
Ocean     	MAX 	MAX 		MAX 	MAX 	MAX 	MAX   MAX  MAX


Cost Matrix for Bird

From/to High mountain Middle mountain Foothills Plain Forest Desert Beach Ocean
High
Mountain  	2 	3 		3 	2 	3 	MAX    5    7
Middle
Mountain  	1 	2 		1 	3 	4 	MAX    4    7
Foothills 	2	3 		2 	2 	3 	MAX    3    4
Plain 	 	2	4 		2 	2 	3 	MAX    3    2
Forest   	4 	4 		3 	3 	3 	MAX    2    3
Desert   	MAX 	MAX 		MAX 	MAX 	MAX	MAX   MAX  MAX
Beach     	4 	5 		3 	2 	3 	MAX    2    2
Ocean     	5	5 		4 	3 	3 	MAX    2    2

Cost Matrix for Fish

From/to High mountain Middle mountain Foothills Plain Forest Desert Beach Ocean
High
Mountain  	MAX 	MAX 		MAX 	MAX 	MAX 	MAX   NAX  MAX
Middle
Mountain  	MAX 	MAX 		MAX 	MAX 	MAX 	MAX   MAX  MAX
Foothills 	MAX	MAX 		MAX	MAX 	MAX	MAX   MAX  MAX
Plain 	 	MAX	MAX 		MAX 	MAX 	MAX	NAX   MAX  MAX
Forest   	MAX 	NAX 		MAX 	MAX	MAX	MAX   NAX  MAX
Desert   	MAX 	MAX 		MAX 	MAX 	MAX	MAX   MAX  MAX
Beach     	MAX 	MAX 		MAX 	MAX 	MAX 	MAX    3    2
Ocean     	MAX 	MAX 		MAX 	MAX 	MAX 	MAX    2    1

Cost Matrix for Frog

From/to High mountain Middle mountain Foothills Plain Forest Desert Beach Ocean
High
Mountain  	MAX 	MAX 		MAX 	MAX 	MAX 	MAX   NAX  MAX
Middle
Mountain  	MAX 	MAX 		MAX 	MAX 	MAX 	MAX   MAX  MAX
Foothills 	MAX	MAX 		3 	2 	3 	MAX    4    4
Plain 	 	MAX	MAX 		3 	2 	3 	MAX    2    2
Forest   	MAX 	MAX 		4 	2 	3 	MAX    2    4
Desert   	MAX 	MAX 		MAX 	MAX 	MAX	MAX   MAX  MAX
Beach     	MAX 	MAX 		3 	2 	3 	MAX    1    1
Ocean     	MAX 	MAX 		4 	3 	3 	MAX    1    2

------------------------------------------------------------------------------------------------------

CHARACTERS

FISH
-The fish will spawn in an ocean space not occupied by any other character 
-The fish can move to the ocean and the beach

HUMAN
-The human will spawn in a space that is not High Mountain or Ocean and not occupied by any other character
-The human can move to any other space besides high mountain and ocean

BIRD
-The bird will spawn in a space that is not desert and is not occupied by any other character
-The bird can move to any other space desides desert and can fly over high mountains (low movement cost in mountain areas)

Frog
-The frog will spawn in a space that is not a moountain or desert
-The frog can move to any other space desides mountain or desert.

--------------------------------------------------------------------------------------------------------

MOVEMENT

-Left click on a character to select that character (Due to grid issues, click on top right corner for proper click tracking)
-Right click on a empty grid space to move to that grid space.
-wait until movement ends. Clicking on a different character will continue the previous character's movement for the new character clicked


---------------------------------------------------------------------------------------------------------

TO-DO

