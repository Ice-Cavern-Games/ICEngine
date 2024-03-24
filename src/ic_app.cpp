#include <ic_app.h>
#include <iostream>

using namespace IC;

namespace
{
    // Global App State
    Config app_config;
    bool app_is_running = false;
    bool app_is_exiting = false;
}

bool App::run(const Config *c)
{
    // Copy config over.
    app_config = *c;

    app_is_running = true;

    // while (!app_is_exiting)
    // {
    //     // @TODO
    // }

    std::cout << app_config.name << " ran." << std::endl;

    return true;
}

bool App::is_running()
{
    return app_is_running;
}

void App::exit()
{
    if (!app_is_exiting && app_is_running)
        app_is_exiting = true;
}

const Config &App::config()
{
    return app_config;
}
