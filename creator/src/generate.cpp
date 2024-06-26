#include <sanguis/log_location.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/impl/generator_map.hpp>
#include <sanguis/creator/impl/log_name.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains_if.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::creator::top_result
sanguis::creator::generate(sanguis::creator::top_parameters const &_parameters)
{
  fcppt::log::object log{
      _parameters.log_context(), sanguis::log_location(), sanguis::creator::impl::log_name()};

  FCPPT_LOG_DEBUG(
      log,
      fcppt::log::out << FCPPT_TEXT("Generating world \"") << _parameters.name()
                      << FCPPT_TEXT("\" with seed ") << _parameters.seed())

  sanguis::creator::impl::random::generator gen(_parameters.seed());

  sanguis::creator::impl::result result(
      fcppt::optional::to_exception(
          fcppt::container::find_opt_mapped(
              sanguis::creator::impl::generator_map(), _parameters.name()),
          [&_parameters]
          {
            return sanguis::creator::exception(
                FCPPT_TEXT("Generator ") + _parameters.name().get() + FCPPT_TEXT(" not found!"));
          })
          .get()(sanguis::creator::impl::parameters(
              fcppt::make_ref(log),
              fcppt::make_ref(gen),
              _parameters.spawn_boss(),
              _parameters.opening_count_array())));

  for (auto const opening_type : fcppt::enum_::make_range<sanguis::creator::opening_type>())
  {
    if (result.openings()[opening_type].size() !=
        _parameters.opening_count_array()[opening_type].get())
    {
      throw sanguis::creator::exception{FCPPT_TEXT("Inconsistent opening counts!")};
    }
  }

  if (result.grid().size() != result.background_grid().size())
  {
    throw sanguis::creator::exception{FCPPT_TEXT("Grid sizes do not match!")};
  }

  if (_parameters.spawn_boss().get())
  {
    if (fcppt::not_(fcppt::algorithm::contains_if(
            result.spawns(),
            [](sanguis::creator::spawn const &_spawn)
            { return _spawn.enemy_kind() == sanguis::creator::enemy_kind::boss; })))
    {
      throw sanguis::creator::exception{FCPPT_TEXT("Not boss spawned!")};
    }
  }

  return sanguis::creator::top_result(
      _parameters.seed(),
      fcppt::copy(_parameters.name()),
      _parameters.spawn_boss(),
      std::move(result.grid()),
      std::move(result.background_grid()),
      std::move(result.openings()),
      std::move(result.spawns()),
      std::move(result.destructibles()));
}
