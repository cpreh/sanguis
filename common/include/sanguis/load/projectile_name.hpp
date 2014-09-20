#ifndef SANGUIS_LOAD_PROJECTILE_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_PROJECTILE_NAME_HPP_INCLUDED

#include <sanguis/projectile_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace load
{

SANGUIS_COMMON_SYMBOL
fcppt::string
projectile_name(
	sanguis::projectile_type
);

}
}

#endif
