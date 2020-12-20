#ifndef SANGUIS_CLIENT_LOAD_HUD_CONTEXT_REF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_CONTEXT_REF_HPP_INCLUDED

#include <sanguis/client/load/hud/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace hud
{

using
context_ref
=
fcppt::reference<
	sanguis::client::load::hud::context
>;

}
}
}
}

#endif
