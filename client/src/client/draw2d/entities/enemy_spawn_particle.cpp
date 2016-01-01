#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/enemy_spawn_particle.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/optional_own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/particle.hpp>
#include <sanguis/client/draw2d/entities/particle_name.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/optional_dim.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/optional_background_tile.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/optional/bind.hpp>


sanguis::client::draw2d::entities::optional_own_unique_ptr
sanguis::client::draw2d::entities::enemy_spawn_particle(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::creator::optional_background_tile const _background_tile
)
{
	switch(
		_enemy_type
	)
	{
	case sanguis::creator::enemy_type::zombie00:
	case sanguis::creator::enemy_type::zombie01:
		return
			fcppt::optional::bind(
				_background_tile,
				[
					&_load_parameters,
					_center
				](
					sanguis::creator::background_tile const _tile
				)
				{
					switch(
						_tile
					)
					{
					case sanguis::creator::background_tile::grass:
					case sanguis::creator::background_tile::dirt:
						return
							// TODO: Put this into a class
							sanguis::client::draw2d::entities::optional_own_unique_ptr(
								fcppt::unique_ptr_to_base<
									sanguis::client::draw2d::entities::own
								>(
									fcppt::make_unique_ptr<
										sanguis::client::draw2d::entities::particle
									>(
										_load_parameters,
										sanguis::client::draw2d::entities::particle_name{
											FCPPT_TEXT("dirt_pile")
										},
										sanguis::client::draw2d::z_ordering::ground,
										_center,
										sanguis::client::draw2d::sprite::optional_dim()
									)
								)
							);
					case sanguis::creator::background_tile::nothing:
					case sanguis::creator::background_tile::asphalt:
						return
							sanguis::client::draw2d::entities::optional_own_unique_ptr();
					}

					FCPPT_ASSERT_UNREACHABLE;
				}
			);
	case sanguis::creator::enemy_type::wolf_black:
	case sanguis::creator::enemy_type::wolf_brown:
	case sanguis::creator::enemy_type::wolf_white:
	case sanguis::creator::enemy_type::spider:
	case sanguis::creator::enemy_type::skeleton:
	case sanguis::creator::enemy_type::ghost:
	case sanguis::creator::enemy_type::maggot:
	case sanguis::creator::enemy_type::reaper:
		return
			sanguis::client::draw2d::entities::optional_own_unique_ptr();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
