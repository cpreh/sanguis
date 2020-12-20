#ifndef SANGUIS_MESSAGES_CLIENT_SHARED_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SHARED_PTR_HPP_INCLUDED

#include <sanguis/messages/client/base_fwd.hpp>
#include <fcppt/shared_ptr.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

using
shared_ptr
=
fcppt::shared_ptr<
	sanguis::messages::client::base
>;

}
}
}

#endif
