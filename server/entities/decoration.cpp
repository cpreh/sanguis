#include "decoration.hpp"
#include "base_parameters.hpp"
#include "../damage_types.hpp"
#include "../message_converter.hpp"
#include "../get_dim.hpp"
#include "../../load/decoration_name.hpp"
#include "../../load/context.hpp"

sanguis::server::entities::decoration::decoration(
	server::environment const &env,
	pos_type const &pos,
	space_unit const angle,
	decoration_type::type const dtype)
:
	entity(
		base_parameters(
			env,
			damage::all(messages::mu(1)),
			pos,
			angle,
			angle,
			team::neutral,
			entities::property_map(),
			entity_type::decoration,
			true,
			default_dim(
				env.load().models(),
				load::decoration_name(
					dtype)))),
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
	return message_convert(*this);
}
