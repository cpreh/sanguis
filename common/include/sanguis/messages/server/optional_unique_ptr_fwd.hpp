#ifndef SANGUIS_MESSAGES_SERVER_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/messages/server/unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sanguis::messages::server
{

using optional_unique_ptr = fcppt::optional::object<sanguis::messages::server::unique_ptr>;

}

#endif
