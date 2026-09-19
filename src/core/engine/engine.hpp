#pragma once

namespace Forradia
{
    class engine
    {
      public:
        void start();

      private:
        void poll_events();

        bool running_{true};
    };
}