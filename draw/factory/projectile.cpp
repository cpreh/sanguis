#include "projectile.hpp"
#include "../bullet.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::projectile(
	environment const &env,
	entity_id const id,
	projectile_type::type const ptype)
{
	switch(ptype) {
	case projectile_type::simple_bullet:
		return entity_auto_ptr(
			new bullet(
				env,
				id,
				SGE_TEXT("bullet")
			)
		);
	default:
		throw exception(
			SGE_TEXT("draw::factory::projectile: missing loading code!")
		);
	}
}
