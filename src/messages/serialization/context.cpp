#include <sanguis/messages/serialization/context.hpp>
#include <sanguis/messages/serialization/dispatcher_base.hpp>

sanguis::messages::serialization::context::context()
{
}

sanguis::messages::serialization::context::~context()
{
}

sanguis::messages::serialization::dispatch_map const &
sanguis::messages::serialization::context::handlers() const
{
	return handlers_;
}
