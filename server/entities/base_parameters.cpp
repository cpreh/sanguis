#include "base_parameters.hpp"

sanguis::server::entities::base_parameters::base_parameters(
	environment const &env_,
	armor_array const &armor_,
	pos_type const &center_,
	space_unit const angle_,
	space_unit const direction_,
	team::type const team_,
	property_map const &properties_,
	entity_type::type const type_,
	bool const invulnerable_,
	dim_type const &collision_dim_)
:
	env_(env_),
	armor_(armor_),
	center_(center_),
	angle_(angle_),
	direction_(direction_),
	team_(team_),
	properties_(properties_),
	type_(type_),
	invulnerable_(invulnerable_),
	collision_dim_(collision_dim_)
{}

sanguis::server::environment const &
sanguis::server::entities::base_parameters::env() const
{
	return env_;
}

sanguis::armor_array const &
sanguis::server::entities::base_parameters::armor() const
{
	return armor_;
}

sanguis::server::pos_type const &
sanguis::server::entities::base_parameters::center() const
{
	return center_;
}

sanguis::server::space_unit
sanguis::server::entities::base_parameters::angle() const
{
	return angle_;
}

sanguis::server::space_unit
sanguis::server::entities::base_parameters::direction() const
{
	return direction_;
}

sanguis::server::team::type
sanguis::server::entities::base_parameters::team() const
{
	return team_;
}

sanguis::server::entities::property_map const &
sanguis::server::entities::base_parameters::properties() const
{
	return properties_;
}

sanguis::entity_type::type
sanguis::server::entities::base_parameters::type() const
{
	return type_;
}

bool
sanguis::server::entities::base_parameters::invulnerable() const
{
	return invulnerable_;
}

sanguis::server::dim_type const &
sanguis::server::entities::base_parameters::collision_dim() const
{
	return collision_dim_;
}
