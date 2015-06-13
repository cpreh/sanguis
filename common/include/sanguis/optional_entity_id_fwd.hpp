#ifndef SANGUIS_OPTIONAL_ENTITY_ID_FWD_HPP_INCLUDED
#define SANGUIS_OPTIONAL_ENTITY_ID_FWD_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{

typedef
fcppt::optional<
	sanguis::entity_id
>
optional_entity_id;

}

#endif
