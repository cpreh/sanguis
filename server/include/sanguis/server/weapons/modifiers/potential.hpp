#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_POTENTIAL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_POTENTIAL_HPP_INCLUDED

#include <sanguis/server/weapons/modifiers/container.hpp>
#include <sanguis/server/weapons/modifiers/potential_tag.hpp>
#include <fcppt/strong_typedef_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

template<
	typename Parameters
>
using
potential
=
fcppt::strong_typedef<
	sanguis::server::weapons::modifiers::container<
		Parameters
	>,
	sanguis::server::weapons::modifiers::potential_tag
>;

}
}
}
}

#endif
