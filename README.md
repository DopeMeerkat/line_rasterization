# Line Rasterization
This uses opencv in visual studio to
- Draw a line using Bresenham's Line Algorithm
- Draw a line with Anti-Aliasing

For the first task, I implemented a straightforward Bresenham line algorithm. This allows you to render a line of solid pixels quickly without having to do floating point multiplication.
 
For the second task, I used Xiaolin Wu’s algorithm, which is essentially a modified version of Bresingham. It takes into consideration the magnitude of the error and assigns a brightness value based on the distance between the 2 pixels

The results are shown in `results`