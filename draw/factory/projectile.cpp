#include "projectile.hpp"
#include "../bullet.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::projectile(
	load::context const &ctx,
	entity_id const id,
	system &sys,
	projectile_type::type const ptype)
{
	switch(ptype) {
	case projectile_type::simple_bullet:
		return entity_ptr(
			new bullet(
				ctx,
				id,
				sys,
				SGE_TEXT("bullet")));
	case projectile_type::rocket:
		return entity_ptr(
			new bullet(
				ctx,
				id,
				sys,
				SGE_TEXT("rocket")));
	default:
		throw exception(
			SGE_TEXT("draw::factory::projectile: missing loading code!"));
	}
}
