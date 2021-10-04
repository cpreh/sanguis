#ifndef SANGUIS_MESSAGES_CLIENT_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/messages/client/unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::messages::client
{

using
optional_unique_ptr
=
fcppt::optional::object<
	sanguis::messages::client::unique_ptr
>;

}

#endif
