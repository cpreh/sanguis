#ifndef SANGUIS_MESSAGES_SERVER_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/messages/server/unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
fcppt::optional<
	sanguis::messages::server::unique_ptr
>
optional_unique_ptr;

}
}
}

#endif
