#ifndef SANGUIS_LOAD_FRIEND_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_FRIEND_NAME_HPP_INCLUDED

#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <fcppt/string.hpp>

namespace sanguis::load
{

SANGUIS_COMMON_SYMBOL
fcppt::string friend_name(sanguis::friend_type);

}

#endif
