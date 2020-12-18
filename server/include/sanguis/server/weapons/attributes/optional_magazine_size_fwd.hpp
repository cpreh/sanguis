#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_OPTIONAL_MAGAZINE_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_OPTIONAL_MAGAZINE_SIZE_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/attributes/magazine_size_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace attributes
{

using
optional_magazine_size
=
fcppt::optional::object<
	sanguis::server::weapons::attributes::magazine_size
>;

}
}
}
}

#endif
