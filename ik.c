#include <stdio.h>
#include <math.h>

int lengthOne, lengthTwo, angleOne, angleTwo;

typedef struct{
    double length;
    double angle;
} arm;

typedef struct {
    double x;
    double y;
} point;

void setAngles(arm *armOne, arm *armTwo);
void setLengths(arm *armOne, arm *armTwo);
point computeEndEffector(arm *armOne, arm *armTwo);

int main(int charc, char **charv){
    arm armOne, armTwo; 
    point ee; 

    setLengths(&armOne, &armTwo);
    setAngles(&armOne, &armTwo);

    ee = computeEndEffector(&armOne, &armTwo);
    printf("The End Effector is located at: (%.2f, %.2f)\n", ee.x, ee.y);

    return 0;
}

void setAngles(arm *armOne, arm *armTwo){
    printf("angle of arm one: ");
    scanf("%d", &angleOne);
    printf("angle of arm two: ");
    scanf("%d", &angleTwo);

    armOne->angle = angleOne;
    armTwo->angle = angleTwo;
}

void setLengths(arm *armOne, arm *armTwo){
    printf("length of arm one: ");
    scanf("%d", &lengthOne);
    printf("length of arm two: ");
    scanf("%d", &lengthTwo);

    (*armOne).length = lengthOne;
    (*armTwo).length = lengthTwo;
}

double degreesToRadians(double val){
    return val * M_PI / 180.0;
}

point computeEndEffector(arm *armOne, arm *armTwo){
    double x2 = armOne->length * cos(degreesToRadians(armOne->angle));
    double y2 = armOne->length * sin(degreesToRadians(armOne->angle));

    double totalAngle = armOne->angle + armTwo->angle;
    double xee = x2 + armTwo->length * cos(degreesToRadians(totalAngle));
    double yee = y2 + armTwo->length * sin(degreesToRadians(totalAngle));

    point ee;
    ee.x = xee;
    ee.y = yee;
    return ee;
}

