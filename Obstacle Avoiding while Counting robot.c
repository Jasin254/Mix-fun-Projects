#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OBSTACLES 5  // number of obstacles in the environment
#define MAX_DIST 10      // maximum distance the robot can travel in one step

int main() {
    // initialize random number generator
    srand(time(NULL));

    // initialize robot position and obstacle positions
    int robot_pos = 0;
    int obstacle_pos[NUM_OBSTACLES];
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        obstacle_pos[i] = rand() % (MAX_DIST + 1);
    }

    // initialize obstacle counter
    int num_obstacles = 0;

    // loop until robot reaches end of environment
    while (robot_pos < MAX_DIST) {
        // check for obstacles
        for (int i = 0; i < NUM_OBSTACLES; i++) {
            if (robot_pos == obstacle_pos[i]) {
                printf("Robot encountered obstacle at position %d\n", robot_pos);
                num_obstacles++;
            }
        }

        // move robot forward
        int dist = rand() % (MAX_DIST - robot_pos + 1);  // random distance to travel
        printf("Robot moved forward %d units\n", dist);
        robot_pos += dist;

        // check if robot has reached end of environment
        if (robot_pos >= MAX_DIST) {
            printf("Robot reached end of environment\n");
        }
    }

    // print final obstacle count
    printf("Robot encountered %d obstacles\n", num_obstacles);

    return 0;
}
