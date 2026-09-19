#pragma once

namespace darktale
{
    class i_scene;

    class scene_manager
    {
      public:
        scene_manager();

        void go_to_scene(std::string_view scene_name);

        void update_current_scene();

        void render_current_scene();

        void on_key_down_current_scene(SDL_Keycode key);

        void on_key_up_current_scene(SDL_Keycode key);

        void on_mouse_down_current_scene(Uint8 button);

        void on_mouse_up_current_scene(Uint8 button, int click_speed);

      private:
        void add_scene(std::string_view scene_name, i_scene &scene);

        int current_scene_{0};
        std::unordered_map<int, i_scene &> scenes_;
    };
}