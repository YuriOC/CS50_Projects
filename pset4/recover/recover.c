#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    typedef uint8_t BYTE;

    BYTE header[512];

    int count = 0;

    char filename[9];

    FILE *img;

    while (fread(header, sizeof(BYTE), 512, input))
    {
        if (header[0] == 0xff && header[1] == 0xd8 && header[2] == 0xff &&
            (header[3] & 0xf0) == 0xe0)
        {
            if(count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(header, sizeof(BYTE), 512, img);
                count++;
            } else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(header, sizeof(BYTE), 512, img);
                count++;
            }
        } else
        {
            if(count != 0)
            {
                fwrite(header, sizeof(BYTE), 512, img);
            }
        }
    }

    fclose(img);
    fclose(input);

    return 0;
}

