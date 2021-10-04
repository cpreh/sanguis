#ifndef SANGUIS_LOAD_PICKUP_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_PICKUP_NAME_HPP_INCLUDED

#include <sanguis/pickup_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <fcppt/string.hpp>


namespace sanguis::load
{

SANGUIS_COMMON_SYMBOL
fcppt::string
pickup_name(
	sanguis::pickup_type
);

}

#endif
