#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/impl/place_boss.hpp>
#include <fcppt/text.hpp>

sanguis::creator::spawn
sanguis::creator::impl::place_boss(sanguis::creator::opening_container_array const &_openings)
{
  if (_openings[sanguis::creator::opening_type::exit].empty())
  {
    throw sanguis::creator::exception{FCPPT_TEXT("place_boss called but no exists available")};
  }

  return sanguis::creator::spawn{
      sanguis::creator::spawn_pos{_openings[sanguis::creator::opening_type::exit].at(0).get()},
      sanguis::creator::enemy_type::zombie01,
      sanguis::creator::spawn_type::single,
      sanguis::creator::enemy_kind::boss};
}
