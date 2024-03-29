#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/client/load/model/make_parts.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <sanguis/client/load/resource/context_cref.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sge/core/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::load::model::object::object(
    fcppt::log::object &_log,
    std::filesystem::path &&_path,
    sanguis::client::load::resource::context_cref const _context)
try : path_(std::move(_path)),
    part_result_(sanguis::client::load::model::make_parts(_log, path_, _context)), random_part_()
{
  FCPPT_LOG_DEBUG(
      _log, fcppt::log::out << FCPPT_TEXT("Entering ") << fcppt::filesystem::path_to_string(this->path_))
}
catch (sge::core::exception const &_error)
{
  FCPPT_LOG_ERROR(
      _log,
      fcppt::log::out << FCPPT_TEXT("model \"") << fcppt::filesystem::path_to_string(_path)
                      << FCPPT_TEXT("\": \"") << _error.string() << FCPPT_TEXT('"'))

  throw;
}

sanguis::client::load::model::object::~object() = default;

sanguis::client::load::model::part const &
sanguis::client::load::model::object::operator[](fcppt::string const &_name) const
{
  // TODO(philipp): optionals
  auto const it(this->parts().find(_name));

  if (it == this->parts().end())
  {
    throw sanguis::exception(
        FCPPT_TEXT("Category \"") + _name + FCPPT_TEXT("\" not found in ") +
        fcppt::filesystem::path_to_string(path_));
  }

  return *it->second;
}

sanguis::client::load::model::part const &sanguis::client::load::model::object::random_part(
    sanguis::random_generator &_random_generator) const
{
  if (!random_part_.has_value())
  {
    random_part_ = optional_part_rand(part_rand(
        fcppt::make_ref(_random_generator),
        part_map_distribution(
            part_map_distribution::param_type::min(0U),
            part_map_distribution::param_type::max(this->parts().size() - 1U))));
  }

  return *std::next(
              this->parts().begin(),
              fcppt::cast::to_signed((
                  // TODO(philipp):
                  random_part_.get_unsafe())()))
              ->second;
}

sanguis::client::load::model::object::size_type sanguis::client::load::model::object::size() const
{
  return this->parts().size();
}

sanguis::client::load::model::object::const_iterator
sanguis::client::load::model::object::begin() const
{
  return this->parts().begin();
}

sanguis::client::load::model::object::const_iterator
sanguis::client::load::model::object::end() const
{
  return this->parts().end();
}

sanguis::model::cell_size sanguis::client::load::model::object::cell_size() const
{
  return part_result_.cell_size();
}

sanguis::client::load::model::part_map const &sanguis::client::load::model::object::parts() const
{
  return part_result_.parts();
}
