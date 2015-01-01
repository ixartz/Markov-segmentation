### Description

Image segmentation with a Markov random field

### Method

At the first time, the program need to learn the mean and the covariance of
each class. So, it is a supervised method: we need to put one image for each
class in a folder called "classe" at project root. After that, the program
generates randomly a probability map. Finding the optimal map, it does a
simulated annealing. In each step of simulated annealing, the program iterates
on each pixel and changes the pixel class randomly. Knowing if the new class is
better than the old one, it computes the old cost and the new one and it
compares the difference. This new state will be accepted if new cost is better
and if this state respects the Metropolis algorithm.

### Building

The project uses CMake build system:

1. mkdir build && cd build
2. cmake .. && make

### Running

In project root, you can find the generated executable:

    ./markov input output

### Dependencies

* CMake (build tool)
* OpenCV
* Boost: filesystem
* Armadillo
