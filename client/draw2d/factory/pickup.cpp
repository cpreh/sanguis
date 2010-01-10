#include "pickup.hpp"
#include "../entities/model/object.hpp"
#include "../z_ordering.hpp"
#include "../../../pickup_type.hpp"
#include "../../../exception.hpp"
#include "../../../load/pickup_name.hpp"
#include <fcppt/text.hpp>

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type::type
);

}

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::pickup(
	entities::model::parameters const &param_,
	pickup_type::type const ptype
)
{
	return entities::auto_ptr(
		new entities::model::object(
			param_,
			get_texture(
				ptype
			),
			z_ordering::pickup,
			entities::model::needs_healthbar::no,
			entities::model::decay_option::immediate
		)
	);
}

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type::type const ptype
)
{
	switch(ptype)
	{
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
