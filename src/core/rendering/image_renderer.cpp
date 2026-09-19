#include "image_renderer.hpp"
#include "core/assets/image_bank.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace Forradia
{
    void image_renderer::draw_image(int image_name_hash, float x, float y,
                                    float width, float height)
    {
        auto canvas_size{get_canvas_size()};

        auto x_px{static_cast<int>(x * canvas_size.width)};
        auto y_px{static_cast<int>(y * canvas_size.height)};
        auto width_px{static_cast<int>(width * canvas_size.width)};
        auto height_px{static_cast<int>(height * canvas_size.height)};

        auto rect{SDL_Rect{x_px, y_px, width_px, height_px}};

        auto image{_<image_bank>().get_image(image_name_hash)};

        SDL_RenderCopy(_<sdl_device>().renderer_.get(), image.get(), nullptr,
                       &rect);
    }

    void image_renderer::draw_image(std::string_view image_name, float x,
                                    float y, float width, float height)
    {
        auto hash{get_hash(image_name)};

        draw_image(hash, x, y, width, height);
    }
}