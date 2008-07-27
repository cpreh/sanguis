#include "pickup.hpp"
#include "simple_sprite.hpp"
#include "../z_ordering.hpp"
#include "../../pickup_type.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace
{

sge::string const get_texture(
	sanguis::pickup_type::type);

}

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::pickup(
	entity_id const id,
	system &sys,
	pickup_type::type const ptype)
{
	return simple_sprite(
		id,
		sys,
		z_ordering::pickup,
		get_texture(
			ptype));
}

namespace
{

sge::string const get_texture(
	sanguis::pickup_type::type const ptype)
{
	switch(ptype) {
	case sanguis::pickup_type::health:
		return SGE_TEXT("health_pickup");
	case sanguis::pickup_type::weapon:
		throw sge::exception(
			SGE_TEXT("draw::factory::pickup: weapon pickup cannot be created using pickup!"));
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::pickup: missing loading code!"));
	}
}

}
