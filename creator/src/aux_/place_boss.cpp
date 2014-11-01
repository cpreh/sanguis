#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/aux_/place_boss.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::creator::spawn
sanguis::creator::aux_::place_boss(
	sanguis::creator::opening_container_array const &_openings
)
{
	FCPPT_ASSERT_PRE(
		!_openings[
			sanguis::creator::opening_type::exit
		].empty()
	);

	return
		sanguis::creator::spawn{
			sanguis::creator::spawn_pos{
				_openings[
					sanguis::creator::opening_type::exit
				].at(
					0
				).get()
			},
			sanguis::creator::enemy_type::zombie01, // TODO
			sanguis::creator::spawn_type::single,
			sanguis::creator::enemy_kind::boss
		};
}
