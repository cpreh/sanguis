#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_EVENT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_EVENT_HPP_INCLUDED

#include <sanguis/server/entities/property/change_event_fwd.hpp>
#include <sanguis/server/entities/property/diff.hpp>


namespace sanguis::server::entities::property
{

class change_event
{
public:
	explicit
	change_event(
		sanguis::server::entities::property::diff
	);

	[[nodiscard]]
	sanguis::server::entities::property::diff
	diff() const;
private:
	sanguis::server::entities::property::diff diff_;
};

}

#endif
