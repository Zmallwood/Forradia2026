#pragma once

namespace Forradia
{
    class positioned_object
    {
      public:
        point position_{-1, -1};
        std::shared_ptr<object> object_;
    };
}