#include <sanguis/projectile_type.hpp>
#include <sanguis/client/draw2d/entities/bullet.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/projectile.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::projectile(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::projectile_type const _ptype
)
{
	switch(
		_ptype
	)
	{
	case sanguis::projectile_type::aoe:
		break;
	case sanguis::projectile_type::simple_bullet:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::bullet
				>(
					_param,
					FCPPT_TEXT("bullet")
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
