#ifndef SANGUIS_CLIENT_CREATE_SYSTEMS_HPP_INCLUDED
#define SANGUIS_CLIENT_CREATE_SYSTEMS_HPP_INCLUDED

#include <sanguis/client/systems_unique_ptr.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sanguis
{
namespace client
{

sanguis::client::systems_unique_ptr
create_systems(
	fcppt::log::context_reference,
	sanguis::client::args::result const &
);

}
}

#endif
