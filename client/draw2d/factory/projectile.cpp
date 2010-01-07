#include "projectile.hpp"
#include "../entities/bullet.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::projectile(
	entities::model::parameters const &param_
	projectile_type::type const ptype
)
{
	switch(ptype) {
	case projectile_type::simple_bullet:
		return entities::auto_ptr(
			new entities::bullet(
				param_,
				FCPPT_TEXT("bullet")
			)
		);
	}

	throw exception(
		FCPPT_TEXT("draw::factory::projectile: missing loading code!")
	);
}
