#ifndef SANGUIS_DRAW_PARTICLE_PROPERTY_MAP_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_PROPERTY_MAP_HPP_INCLUDED

#include "property_container.hpp"
#include "properties_fwd.hpp"
#include "../../particle_type.hpp"

namespace sanguis
{
namespace draw
{
namespace particle
{
class property_map {
public:
	explicit property_map(
		property_container const &);
	
	properties const &
	operator[](
		particle_type::type) const;
private:
	property_container container_;	
};


}
}
}

#endif
