#ifndef SANGUIS_LOAD_DESTRUCTIBLE_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_DESTRUCTIBLE_NAME_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/creator/destructible_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace load
{

SANGUIS_COMMON_SYMBOL
fcppt::string
destructible_name(
	sanguis::creator::destructible_type
);

}
}

#endif
