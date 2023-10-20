#include <sanguis/creator/count.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/creator/impl/closest_empty.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/place_boss.hpp>
#include <sanguis/creator/impl/place_spawners.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int_wrapper_impl.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/random/wrapper/make_uniform_container_advanced.hpp>

sanguis::creator::spawn_container sanguis::creator::impl::place_spawners(
    fcppt::log::object &_log,
    fcppt::reference<sanguis::creator::grid> const _grid,
    sanguis::creator::opening_container_array const &_openings,
    sanguis::creator::count const _spawner_count,
    sanguis::creator::impl::random::generator &_generator,
    sanguis::creator::impl::enemy_type_container const &_enemy_types,
    sanguis::creator::spawn_boss const _spawn_boss,
    sanguis::creator::tile const _spawner_tile)
{
  sanguis::creator::impl::random::uniform_pos random_pos{
      fcppt::make_ref(_generator), _grid->size()};

  auto random_monster{fcppt::optional::to_exception(
      fcppt::random::wrapper::make_uniform_container_advanced<
          sanguis::creator::impl::random::uniform_int_wrapper>(fcppt::make_cref(_enemy_types)),
      [] { return sanguis::creator::exception{FCPPT_TEXT("Monster range empty!")}; })};

  sanguis::creator::spawn_container spawners{};

  if (_spawn_boss.get())
  {
    spawners.push_back(sanguis::creator::impl::place_boss(_openings));
  }

  sanguis::creator::spawn_container::size_type current_spawners{0U};

  sanguis::creator::count iterations{0U};

  while (current_spawners < _spawner_count)
  {
    sanguis::creator::pos const candidate{fcppt::optional::to_exception(
        sanguis::creator::impl::closest_empty(_grid.get(), random_pos()),
        [] {
          return sanguis::creator::exception{FCPPT_TEXT("Could not find a free tile anywhere!")};
        })};

    if (
        // TODO(philipp): Use any_of for ranges
        !fcppt::algorithm::fold(
            _openings[sanguis::creator::opening_type::entry],
            false,
            [&_grid, &candidate](sanguis::creator::opening const &_cur, bool const _value) {
              return _value ||
                     sanguis::creator::tile_is_visible(_grid.get(), candidate, _cur.get());
            }))
    {
      fcppt::optional::to_exception(
          fcppt::container::grid::at_optional(_grid.get(), candidate),
          [] { return sanguis::creator::exception{FCPPT_TEXT("Spawner tile out of range!")}; })
          .get() = _spawner_tile;

      // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
      spawners.push_back(sanguis::creator::spawn{
          sanguis::creator::spawn_pos{candidate},
          random_monster(_generator),
          sanguis::creator::spawn_type::spawner,
          sanguis::creator::enemy_kind::normal});

      ++current_spawners;
    }

    if (++iterations > _spawner_count * 5)
    {
      FCPPT_LOG_ERROR(
          _log,
          fcppt::log::out << FCPPT_TEXT("gave up on placing ")
                          << (_spawner_count - current_spawners)
                          << FCPPT_TEXT(" spawners due to visibility after ") << iterations
                          << FCPPT_TEXT(" tries."))

      break;
    }
  }

  return spawners;
}
