#include "pickup.hpp"
#include "../model.hpp"
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
	return entity_ptr(
		new model(
			id,
			sys,
			get_texture(
				ptype),
			z_ordering::pickup));
}

namespace
{

sge::string const get_texture(
	sanguis::pickup_type::type const ptype)
{
	switch(ptype) {
	case sanguis::pickup_type::health:
		return SGE_TEXT("pickup_hp");
	case sanguis::pickup_type::weapon:
		throw sge::exception(
			SGE_TEXT("draw::factory::pickup: weapon pickup cannot be created using pickup!"));
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::pickup: missing loading code!"));
	}
}

}
