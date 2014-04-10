#ifndef SANGUIS_LOAD_ENEMY_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_ENEMY_NAME_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace load
{

SANGUIS_COMMON_SYMBOL
fcppt::string
enemy_name(
	sanguis::creator::enemy_type
);

}
}

#endif
