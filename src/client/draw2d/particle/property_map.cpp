#include "property_map.hpp"
#include "properties.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::property_map::property_map(
	property_container const &_container
)
:
	container_(_container)
{
}

sanguis::client::draw2d::particle::properties const &
sanguis::client::draw2d::particle::property_map::operator[](
	particle_type::type const _type
) const
{
	particle::property_container::const_iterator const it(
		container_.find(
			_type
		)
	);
	
	// TODO: maybe provide a default here?
	if(
		it == container_.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Property not found in particle!")
		);

	return it->second;
}
