#include <sanguis/load/model/path_to_json_file.hpp>

std::filesystem::path sanguis::load::model::path_to_json_file(std::filesystem::path const &_path)
{
  return (_path / _path.stem()).replace_extension("json");
}
