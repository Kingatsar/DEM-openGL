#ifndef FPCONTROLS_H
#define FPCONTROLS_H

#include "controls.h"

class FPControls : public Controls
{
public:
    FPControls(GLFWwindow* window, Camera* camera);
    void update(float deltaTime, Shader* shader);
};

#endif // FPSCONTROLS_H
