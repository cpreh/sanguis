#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_TO_FLOAT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_TO_FLOAT_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

template<
	typename Float
>
Float
to_float(
	value const &_value
)
{
	return
		static_cast<
			Float
		>(
			_value
		);
}

}
}
}
}

#endif
