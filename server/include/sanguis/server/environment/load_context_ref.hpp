#ifndef SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_REF_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_REF_HPP_INCLUDED

#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::server::environment
{

using load_context_ref = fcppt::reference<sanguis::server::environment::load_context>;

}

#endif
