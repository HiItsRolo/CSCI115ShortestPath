# CSCI115ShortestPath
Project for class using dijkstra shortest path algorithm and midpoint algorithm for terrain generation.

========================================================================================================

TERRAIN GENERATION

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
(e.g top-left corner will be (0,gridsize).

-Initialized by calling M->generateTerrain();


-------------------