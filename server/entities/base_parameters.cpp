#include "base_parameters.hpp"
#include "insert_default_properties.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/container/map_impl.hpp>

sanguis::server::entities::base_parameters::base_parameters(
	environment::load_context_ptr const load_context_,
	damage::armor const &armor_,
	team::type const team_,
	property_map const &properties_,
	entity_type::type const type_,
	bool const invulnerable_,
	dim_type const &collision_dim_
)
:
	load_context_(load_context_),
	armor_(armor_),
	team_(team_),
	properties_(
		insert_default_properties(
			properties_
		)
	),
	type_(type_),
	invulnerable_(invulnerable_),
	collision_dim_(collision_dim_)
{}

sanguis::server::environment::load_context_ptr const
sanguis::server::entities::base_parameters::load_context() const
{
	return load_context_;
}

sanguis::server::damage::armor const &
sanguis::server::entities::base_parameters::armor() const
{
	return armor_;
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
