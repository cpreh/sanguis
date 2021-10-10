#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/function_impl.hpp>

namespace sanguis::server
{

using send_callback = fcppt::function<void(sanguis::messages::server::base const &)>;

}

#endif
