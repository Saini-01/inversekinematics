#include <stdio.h>

int lengthOne, lengthTwo, angleOne, angleTwo;

typedef struct{
    double length;
    double angle;
} arm;

void setAngles(arm *armOne, arm *armTwo);
void setLengths(arm *armOne, arm *armTwo);

int main(int charc, char **charv){
    arm armOne, armTwo; 

    setLengths(&armOne, &armTwo);
    setAngles(&armOne, &armTwo);

    return 0;
}

void setAngles(arm *armOne, arm *armTwo){
    printf("angle of arm one: ");
    scanf("%d", &angleOne);
    printf("angle of arm two: ");
    scanf("%d", &angleTwo);

    (*armOne).angle = angleOne;
    (*armTwo).angle = angleTwo;
}

void setLengths(arm *armOne, arm *armTwo){
    printf("length of arm one: ");
    scanf("%d", &lengthOne);
    printf("length of arm two: ");
    scanf("%d", &lengthTwo);

    (*armOne).length = lengthOne;
    (*armTwo).length = lengthTwo;
}
