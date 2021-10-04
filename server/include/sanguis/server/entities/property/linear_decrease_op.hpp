#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_DECREASE_OP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_DECREASE_OP_HPP_INCLUDED

#include <sanguis/server/entities/property/apply.hpp>
#include <sanguis/server/entities/property/base_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>


namespace sanguis::server::entities::property
{

void
linear_decrease_op(
	sanguis::server::entities::property::base &, // NOLINT(google-runtime-references)
	sanguis::server::entities::property::value,
	sanguis::server::entities::property::apply
);

}

#endif
