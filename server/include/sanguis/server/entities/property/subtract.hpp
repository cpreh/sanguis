#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_SUBTRACT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_SUBTRACT_HPP_INCLUDED

#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>

namespace sanguis::server::entities::property
{

void subtract(
    sanguis::server::entities::property::changeable &, // NOLINT(google-runtime-references)
    sanguis::server::entities::property::value const &);

}

#endif
