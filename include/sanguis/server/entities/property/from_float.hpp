#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED

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
value
from_float(
	Float const _float
)
{
	return
		static_cast<
			value
		>(
			_float
		);
}

}
}
}
}

#endif
