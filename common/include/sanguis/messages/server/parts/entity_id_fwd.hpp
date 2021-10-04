#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_ID_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/entity_id_fwd.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::server::parts
{

using
entity_id
=
fcppt::record::element<
	sanguis::messages::roles::entity_id,
	sanguis::messages::adapted_types::entity_id
>;

}

#endif
