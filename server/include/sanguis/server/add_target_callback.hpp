#ifndef SANGUIS_SERVER_ADD_TARGET_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ADD_TARGET_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/function_impl.hpp>

namespace sanguis::server
{

using add_target_callback = fcppt::function<void(sanguis::server::entities::with_body_ref)>;

}

#endif
