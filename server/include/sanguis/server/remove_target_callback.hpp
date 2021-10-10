#ifndef SANGUIS_SERVER_REMOVE_TARGET_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_REMOVE_TARGET_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/function_impl.hpp>

namespace sanguis::server
{

using remove_target_callback = fcppt::function<void(sanguis::server::entities::with_body &)>;

}

#endif
