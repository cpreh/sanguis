#ifndef SANGUIS_CLIENT_LEVEL_HPP_INCLUDED
#define SANGUIS_CLIENT_LEVEL_HPP_INCLUDED

#include <sanguis/messages/types/level.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::client
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::messages::types::level, level);

}

#endif
