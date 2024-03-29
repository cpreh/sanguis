#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_SPECIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_SPECIAL_HPP_INCLUDED

#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/is_unique.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>

namespace sanguis::server::entities::enemies::factory
{

sanguis::server::entities::with_id_unique_ptr make_special(
    sanguis::random_generator_ref,
    sanguis::server::entities::enemies::parameters &&,
    sanguis::server::entities::enemies::is_unique);

}

#endif
