#ifndef SANGUIS_MESSAGES_SERVER_SHARED_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SHARED_PTR_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/shared_ptr.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
shared_ptr
=
fcppt::shared_ptr<
	sanguis::messages::server::base
>;

}
}
}

#endif
