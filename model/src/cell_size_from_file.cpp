#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/cell_size_from_file.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/impl/deserialize/cell_size.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sanguis::model::cell_size sanguis::model::cell_size_from_file(std::filesystem::path const &_path)
try
{
  return sanguis::model::impl::deserialize::cell_size(
      sge::parse::json::parse_file_exn(_path).object());
}
catch (fcppt::exception const &_error)
{
  throw sanguis::model::exception{fcppt::string{_error.string()}};
}
