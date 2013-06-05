#ifndef SANGUIS_SERVER_DAMAGE_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARRAY_HPP_INCLUDED

#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

typedef std::array<
	sanguis::server::damage::unit,
	static_cast<
		std::size_t
	>(
		fcppt::enum_size<
			sanguis::server::damage::type
		>::value
	)
> array;

}
}
}

#endif
