#include "App.h"

int main(void)
{
    auto app = new App();
    app->initialization();

    app->createLights();
    app->createShaders();
    app->createModels();
    app->run();
}