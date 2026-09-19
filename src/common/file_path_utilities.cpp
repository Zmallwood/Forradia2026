#include "file_path_utilities.hpp"

namespace darktale
{
    std::string get_file_name_no_ext(std::string_view path)
    {
        auto file_name{std::filesystem::path(path).filename().string()};

        return file_name.substr(0, file_name.find_last_of("."));
    }
}