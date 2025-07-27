#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct{
    double length;
    double angle;
} arm;

typedef struct{
    double x;
    double y;
} point;

typedef struct{
    double t1;
    double t2;
} thetas;

void setAngles(arm *armOne, arm *armTwo);
void setLengths(arm *armOne, arm *armTwo);
point computeEndEffector(arm *armOne, arm *armTwo);
thetas solveIK(point target, arm *armOne, arm *armTwo);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int charc, char **charv){

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Double Jointed Arm", NULL, NULL);

     if (window == NULL){
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoaderLoadGL()) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    arm armOne, armTwo; 
    point ee, target;
    char bool[4];
    thetas result;

    setLengths(&armOne, &armTwo);
    setAngles(&armOne, &armTwo);

    ee = computeEndEffector(&armOne, &armTwo);
    printf("The End Effector is located at: (%.2f, %.2f)\n", ee.x, ee.y);

    printf("Do you have a specific point you want to reach? (y/n)");
    scanf("%s", bool); 

    if(strcmp(bool, "y") == 0){
        printf("X value of target: ");
        scanf("%lf", &target.x);
        printf("Y value of target: ");
        scanf("%lf", &target.y);
        result = solveIK(target, &armOne, &armTwo);
        printf("Value of theta for arm one: %.2f.\nValue of theta for arm two: %.2f.\n", result.t1, result.t2);
    }
    else{
        return 1;
    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}

void setAngles(arm *armOne, arm *armTwo){
    printf("angle of arm one: ");
    scanf("%lf", &armOne->angle);
    printf("angle of arm two: ");
    scanf("%lf", &armTwo->angle);
}

void setLengths(arm *armOne, arm *armTwo){
    printf("length of arm one: ");
    scanf("%lf", &armOne->length);
    printf("length of arm two: ");
    scanf("%lf", &armTwo->length);
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

thetas solveIK(point target, arm *armOne, arm *armTwo){
    double x = target.x;
    double y = target.y;
    double L1 = armOne->length;
    double L2 = armTwo->length;
    double D = sqrt(x*x + y*y);
    thetas t;

    if (D > L1 + L2) {
        printf("Target is not reachable.\n");
        thetas errorTheta = { -1, -1 };
        return errorTheta;
    }

    double cosTheta2 = (x*x + y*y - L1*L1 - L2*L2) / (2 * L1 * L2);
    double theta2 = acos(cosTheta2); 

    double k1 = L1 + L2 * cos(theta2);
    double k2 = L2 * sin(theta2);
    double theta1 = atan2(y, x) - atan2(k2, k1);

    armOne->angle = theta1 * 180.0 / M_PI;
    armTwo->angle = theta2 * 180.0 / M_PI;

    t.t1 = armOne->angle;
    t.t2 = armTwo->angle;

    return t;
}
