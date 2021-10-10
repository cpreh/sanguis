#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/entities/property/change_event_fwd.hpp>

namespace sanguis::server::entities::property
{

using change_function = void(sanguis::server::entities::property::change_event const &);

}

#endif
