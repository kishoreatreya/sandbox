#include <stdio.h>

int main(int argc, char* argv[])
{
    char name[24];

    printf("Enter Your Name: ");
    scanf("%s", name);

    printf("Hello %s\n", name);

    return 0;
}
