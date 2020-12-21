#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_CONTEXT_CREF_HPP_INCLUDED

#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

using
context_cref
=
fcppt::reference<
	sanguis::client::load::resource::context const
>;

}
}
}
}

#endif
