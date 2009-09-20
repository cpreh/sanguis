#ifndef SANGUIS_SERVER_ENTITIES_BASE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_PARAMETERS_HPP_INCLUDED

#include "property_map.hpp"
#include "property.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../dim_type.hpp"
#include "../team.hpp"
#include "../damage/armor.hpp"
#include "../../entity_type.hpp"
#include <sge/container/map_decl.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/math/dim/basic_decl.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class base_parameters {
public:
	base_parameters(
		environment::load_context_ptr,
		damage::armor const &,
		team::type team_,
		property_map const &properties,
		entity_type::type type_,
		bool invulnerable,
		dim_type const &collision_dim
	);
	
	environment::load_context_ptr const
	load_context() const;

	damage::armor const &
	armor() const;

	space_unit
	angle() const;

	space_unit
	direction() const;

	server::team::type
	team() const;

	property_map const &
	properties() const;

	entity_type::type
	type() const;

	bool
	invulnerable() const;

	dim_type const &
	collision_dim() const;
private:
	environment::load_context_ptr const load_context_;
	damage::armor const        &armor_;
	server::team::type const   team_;
	property_map const         properties_;
	entity_type::type const    type_;
	bool const                 invulnerable_;
	dim_type const             collision_dim_;
};

}
}
}

#endif
