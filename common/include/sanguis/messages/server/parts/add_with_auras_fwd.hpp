#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_AURAS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_AURAS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/aura_type_vector_fwd.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::server::parts
{

using
add_with_auras
=
fcppt::record::element<
	sanguis::messages::roles::aura_type_container,
	sanguis::messages::adapted_types::aura_type_vector
>;

}

#endif
