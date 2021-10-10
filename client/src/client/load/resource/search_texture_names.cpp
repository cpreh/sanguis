#include <sanguis/media_path.hpp>
#include <sanguis/client/load/resource/parse_texture_file.hpp>
#include <sanguis/client/load/resource/search_texture_names.hpp>
#include <sanguis/client/load/resource/texture_name_map.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::load::resource::texture_name_map
sanguis::client::load::resource::search_texture_names(fcppt::log::object &_log)
{
  return fcppt::algorithm::fold(
      boost::make_iterator_range(
          std::filesystem::directory_iterator(sanguis::media_path()),
          std::filesystem::directory_iterator()),
      sanguis::client::load::resource::texture_name_map(),
      [&_log](
          std::filesystem::path const &_path,
          sanguis::client::load::resource::texture_name_map &&_result)
      {
        return std::filesystem::is_regular_file(_path) &&
                       fcppt::filesystem::extension(_path) == FCPPT_TEXT(".tex")
                   ? sanguis::client::load::resource::parse_texture_file(
                         _log, _path, std::move(_result))
                   : _result;
      });
}
