#ifndef SANGUIS_MESSAGES_SERVER_PARTS_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_SPEED_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::messages::server::parts
{

using
speed
=
fcppt::record::element<
	sanguis::messages::roles::speed,
	sanguis::messages::adapted_types::vector2
>;

}

#endif
