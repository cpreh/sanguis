#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server::parts
{

using add_with_health = fcppt::mpl::list::object<
    fcppt::record::
        element<sanguis::messages::roles::health, sanguis::messages::adapted_types::space_unit>,
    fcppt::record::element<
        sanguis::messages::roles::max_health,
        sanguis::messages::adapted_types::space_unit>>;

}

#endif
