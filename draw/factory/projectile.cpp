#include "projectile.hpp"
#include "../bullet.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::projectile(
	entity_id const id,
	system &sys,
	projectile_type::type const ptype)
{
	switch(ptype) {
	case projectile_type::simple_bullet:
		return entity_ptr(
			new bullet(
				id,
				sys,
				SGE_TEXT("bullet")));
	case projectile_type::rocket:
		return entity_ptr(
			new bullet(
				id,
				sys,
				SGE_TEXT("rocket")));
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::projectile: missing loading code!"));
	}
}
