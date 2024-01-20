#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_DIFF_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_DIFF_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::property
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::entities::property::value, diff);

}

#endif
