#include <sanguis/client/draw2d/factory/projectile.hpp>
#include <sanguis/client/draw2d/entities/bullet.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::projectile(
	entities::model::parameters const &_param,
	projectile_type::type const _ptype
)
{
	switch(
		_ptype
	)
	{
	case projectile_type::aoe:
	case projectile_type::melee:
	case projectile_type::size:
		break;
	case projectile_type::simple_bullet:
		return
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::bullet
				>(
					fcppt::cref(
						_param
					),
					FCPPT_TEXT("bullet")
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
