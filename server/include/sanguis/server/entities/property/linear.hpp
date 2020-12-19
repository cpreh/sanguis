#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_HPP_INCLUDED

#include <sanguis/server/entities/property/linear_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class linear
{
public:
	linear();

	void
	change(
		sanguis::server::entities::property::value
	);

	[[nodiscard]]
	sanguis::server::entities::property::value
	value() const;
private:
	sanguis::server::entities::property::value value_;
};

}
}
}
}

#endif
