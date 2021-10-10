#ifndef SANGUIS_SERVER_AI_CONTEXT_REF_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CONTEXT_REF_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::server::ai
{

using context_ref = fcppt::reference<sanguis::server::ai::context>;

}

#endif
