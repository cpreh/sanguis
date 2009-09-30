#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_DECL_HPP_INCLUDED

#include "linear_fwd.hpp"
#include "value.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class linear {
public:
	typedef property::value value_type;

	linear();

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
