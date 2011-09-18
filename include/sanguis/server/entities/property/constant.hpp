#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CONSTANT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CONSTANT_HPP_INCLUDED

#include <sanguis/server/entities/property/constant_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class constant
{
public:
	typedef property::value value_type;

	constant();

	void
	change(
		value_type
	);

	value_type
	value() const;
private:
	value_type value_;
};

}
}
}
}

#endif
