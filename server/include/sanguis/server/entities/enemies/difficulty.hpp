#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_DIFFICULTY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_DIFFICULTY_HPP_INCLUDED

#include <sanguis/server/entities/enemies/difficulty_value.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::enemies
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::entities::enemies::difficulty_value, difficulty);

}

#endif
