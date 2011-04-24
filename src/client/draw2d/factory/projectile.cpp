#include "projectile.hpp"
#include "../entities/bullet.hpp"
#include "../../../exception.hpp"
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
					_param,
					FCPPT_TEXT("bullet")
				)
			);
	}

	throw sanguis::exception(
		FCPPT_TEXT("draw::factory::projectile: missing loading code!")
	);
}
