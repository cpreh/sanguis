#ifndef SANGUIS_SERVER_ENTITIES_BASE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_PARAMETERS_HPP_INCLUDED

#include "property_map.hpp"
#include "property.hpp"
#include "../dim_type.hpp"
#include <sge/container/map_decl.hpp>
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
		property_map const &properties,
		dim_type const &collision_dim
	);
	
	property_map const &
	properties() const;

	dim_type const &
	collision_dim() const;
private:
	property_map const properties_;
	dim_type const collision_dim_;
};

}
}
}

#endif
