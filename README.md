# Implementation of a precedence graph using named semaphores

Implement the following precedence graph using named semaphores.

Originally the idea was to implement using unnamed semaphores, but MacOS doesn't support them because they are optional in POSIX. This implementation compile without warnings on MacOS and perform as expected.

![](https://github.com/geanceretta/semaphores_precedence_graph/blob/master/graph.png)
