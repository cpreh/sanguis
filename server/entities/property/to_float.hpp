#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_TO_FLOAT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_TO_FLOAT_HPP_INCLUDED

#include "value.hpp"

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
	value const &value_
)
{
	return static_cast<Float>(value_);
	/*
	return boost::rational_cast<
		Float
	>(
		value_
	);*/
}

}
}
}
}

#endif
