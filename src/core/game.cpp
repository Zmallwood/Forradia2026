#include "game.hpp"
#include "engine/engine.hpp"

namespace darktale
{
    void game::start()
    {
        _<engine>().start();
    }
}