#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }

    FILE *res = NULL;
    BYTE buffer[512];
    int j = 0;
    char filename[] = {0, 0, 0, 0, 0, 0, 0, 0};

    while (fread(buffer, sizeof(BYTE) * 512, 1, file) == 1)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            if (res != NULL)
            {
                fclose(res);
            }
            sprintf(filename, "%03d.jpg", j++);
            res = fopen(filename, "w");
        }
        if (res != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, res);
        }
    }
    if (res != NULL)
    {
        fclose(res);
    }
    fclose(file);
    return 0;
}