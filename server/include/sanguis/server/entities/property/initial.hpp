#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_INITIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_INITIAL_HPP_INCLUDED

#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


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
	FCPPT_MAKE_STRONG_TYPEDEF(
		sanguis::server::entities::property::value,
		base
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sanguis::server::entities::property::value,
		current
	);

	initial(
		sanguis::server::entities::property::initial::base,
		sanguis::server::entities::property::initial::current
	);

	sanguis::server::entities::property::value
	get_base() const;

	sanguis::server::entities::property::value
	get_current() const;
private:
	sanguis::server::entities::property::value
		base_,
		current_;
};

}
}
}
}

#endif
