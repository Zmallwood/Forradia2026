#pragma once

namespace darktale
{
    class point
    {
      public:
        auto operator<=>(const point &) const = default;

        int x{0};
        int y{0};
    };
}