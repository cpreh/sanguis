#include "pickup.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../pickup_type.hpp"
#include "../../load/pickup_name.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

namespace
{

sge::string const
get_texture(
	sanguis::pickup_type::type);

}

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::pickup(
	environment const &env,
	entity_id const id,
	system &sys,
	pickup_type::type const ptype)
{
	return entity_auto_ptr(
		new model(
			env,
			id,
			sys,
			get_texture(
				ptype),
			z_ordering::pickup,
			false));
}

namespace
{

sge::string const
get_texture(
	sanguis::pickup_type::type const ptype)
{
	switch(ptype) {
	case sanguis::pickup_type::health:
		return sanguis::load::pickup_name(ptype);
	case sanguis::pickup_type::weapon:
		throw sanguis::exception(
			SGE_TEXT("draw::factory::pickup: weapon pickup cannot be created using pickup!"));
	default:
		throw sanguis::exception(
			SGE_TEXT("draw::factory::pickup: missing loading code!"));
	}
}

}
