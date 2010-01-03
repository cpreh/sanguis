#include "pickup.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../pickup_type.hpp"
#include "../../load/pickup_name.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type::type);

}

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::pickup(
	environment const &env,
	entity_id const id,
	pickup_type::type const ptype)
{
	return entity_auto_ptr(
		new model(
			env,
			id,
			get_texture(
				ptype),
			z_ordering::pickup,
			false,
			remove_action::remove));
}

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type::type const ptype)
{
	switch(ptype) {
	case sanguis::pickup_type::monster:
	case sanguis::pickup_type::health:
		return sanguis::load::pickup_name(ptype);
	case sanguis::pickup_type::weapon:
		throw sanguis::exception(
			FCPPT_TEXT("draw::factory::pickup: weapon pickup cannot be created using pickup!"));
	case sanguis::pickup_type::size:
		break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("draw::factory::pickup: missing loading code!")
	);
}

}