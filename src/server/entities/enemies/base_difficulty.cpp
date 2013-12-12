#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/enemies/base_difficulty.hpp>
#include <sanguis/server/entities/enemies/difficulty_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::entities::enemies::difficulty_value
sanguis::server::entities::enemies::base_difficulty(
	sanguis::creator::enemy_type const _enemy_type
)
{
	switch(
		_enemy_type
	)
	{
	case sanguis::creator::enemy_type::wolf_black:
	case sanguis::creator::enemy_type::wolf_brown:
	case sanguis::creator::enemy_type::wolf_white:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				3
			);
	case sanguis::creator::enemy_type::zombie00:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				2
			);
	case sanguis::creator::enemy_type::zombie01:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				2
			);
	case sanguis::creator::enemy_type::spider:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				5
			);
	case sanguis::creator::enemy_type::skeleton:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				8
			);
	case sanguis::creator::enemy_type::ghost:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				5
			);
	case sanguis::creator::enemy_type::maggot:
		return
			fcppt::literal<
				sanguis::server::entities::enemies::difficulty_value
			>(
				1
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
