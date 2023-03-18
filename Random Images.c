#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int width = 40;
    int height = 20;
    int image[height][width];

    srand(time(NULL)); // initialize random seed

    // generate random image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = rand() % 2;
        }
    }

    // print image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j] == 0)
            {
                printf(".");
            }
            else
            {
                printf("*");
            }
        }
        printf("\n");
    }

    return 0;
}
