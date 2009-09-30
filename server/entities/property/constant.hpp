#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CONSTANT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CONSTANT_HPP_INCLUDED

#include "constant_fwd.hpp"
#include "value.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class constant {
public:
	typedef property::value value_type;

	constant();

	void
	add(
		value_type
	);

	void
	remove(
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
