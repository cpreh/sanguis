#include "decoration.hpp"
#include "base_parameters.hpp"
#include "property.hpp"
#include "../damage_types.hpp"
#include "../get_dim.hpp"
#include "../../load/decoration_name.hpp"
#include "../../load/context.hpp"
#include "../../messages/create.hpp"
#include "../../messages/add_decoration.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::decoration::decoration(
	server::environment const &env,
	pos_type const &pos,
	space_unit const angle,
	decoration_type::type const dtype)
:
	entity(
		base_parameters(
			env,
			damage::all(static_cast<space_unit>(1)),
			pos,
			angle,
			angle,
			team::neutral,
			boost::assign::map_list_of
				(entities::property_type::health,
				entities::property(static_cast<space_unit>(1))),
			entity_type::decoration,
			true,
			default_dim(
				env.load()().models(),
				load::decoration_name(
					dtype
				)
			)
		)
	),
	type_(dtype)
{}

sanguis::decoration_type::type
sanguis::server::entities::decoration::dtype() const
{
	return type_;
}

sanguis::messages::auto_ptr
sanguis::server::entities::decoration::add_message() const
{
	return messages::create(
		messages::add_decoration(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			dtype()
		)
	);
}
