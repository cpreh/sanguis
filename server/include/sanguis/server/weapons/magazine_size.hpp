#ifndef SANGUIS_SERVER_WEAPONS_MAGAZINE_SIZE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MAGAZINE_SIZE_HPP_INCLUDED

#include <sanguis/magazine_type.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::weapons
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::magazine_type, magazine_size);

}

#endif
