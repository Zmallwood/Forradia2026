#include "game.hpp"
#include "engine/engine.hpp"

namespace Forradia
{
    void game::start()
    {
        _<engine>().start();
    }
}