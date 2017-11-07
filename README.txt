Aaron Gordon 0884023
CIS*3090 Assignment 3

Program should be fully operational. Couple of notes I found neat:
- Small matrix sizes sometimes has a faster time for 1 thread than multiple, initialization of threads maybe causing time costs?
- Moderate matrix sizes seems to favour having 2 threads as though the small matrix problem is still apparent but still faster to have moderate thread count as opposed to 1 thread.
- As expected, larger matrix sizes have the larger thread count make the program run faster.

A note for the code: -g will take a bit of time. This is largely in part to the randomization of the matrix initialization, which for 20000 x 20000 ints calls the randomizer a lot of times. This should not impact the data or the accuracy in any way but it was assumed that the entire omp blocks are to be included in the time returned.