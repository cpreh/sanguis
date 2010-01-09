#include "property_map.hpp"
#include "properties.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::property_map::property_map(
	property_container const &container_
)
:
	container_(container_)
{}

sanguis::client::draw2d::particle::properties const &
sanguis::client::draw2d::particle::property_map::operator[](
	particle_type::type const pt
) const
{
	particle::property_container::const_iterator const it(
		container_.find(
			pt
		)
	);
	
	// TODO: maybe provide a default here?
	if(it == container_.end())
		throw exception(
			FCPPT_TEXT("Property not found in particle!")
		);

	return it->second;
}
