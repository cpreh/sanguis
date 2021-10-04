#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_DIFF_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_DIFF_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::entities::property
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::property::value,
	diff
);

}

#endif
