#include <sanguis/load/model/path_to_json_file.hpp>
#include <fcppt/copy.hpp>

std::filesystem::path sanguis::load::model::path_to_json_file(std::filesystem::path const &_path)
{
  return fcppt::copy(_path).replace_extension("json");
}
