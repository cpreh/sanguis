#ifndef SANGUIS_SERVER_WEAPONS_INSERT_TO_ATTACK_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_INSERT_TO_ATTACK_RESULT_HPP_INCLUDED

#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>

namespace sanguis::server::weapons
{

sanguis::server::weapons::attack_result
insert_to_attack_result(sanguis::server::entities::optional_base_ref const &);

}

#endif
