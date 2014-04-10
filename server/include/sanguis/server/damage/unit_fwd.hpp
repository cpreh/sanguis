#ifndef SANGUIS_SERVER_DAMAGE_UNIT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_UNIT_FWD_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::space_unit,
	unit
);

}
}
}

#endif
