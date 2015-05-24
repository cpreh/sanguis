#ifndef SANGUIS_CLIENT_SYSTEMS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_SYSTEMS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/systems_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{

typedef
fcppt::unique_ptr<
	sanguis::client::systems
>
systems_unique_ptr;

}
}

#endif
