#ifndef SANGUIS_MESSAGES_CLIENT_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/messages/client/unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
fcppt::optional<
	sanguis::messages::client::unique_ptr
>
optional_unique_ptr;

}
}
}

#endif
