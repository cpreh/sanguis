#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_INITIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_INITIAL_HPP_INCLUDED

#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class initial
{
public:
	typedef property::value value_type;

	initial(
		value_type base,
		value_type current
	);

	value_type
	base() const;

	value_type
	current() const;
private:
	value_type
		base_,
		current_;
};

}
}
}
}

#endif
