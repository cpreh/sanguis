#ifndef SANGUIS_CLIENT_CREATE_SYSTEMS_HPP_INCLUDED
#define SANGUIS_CLIENT_CREATE_SYSTEMS_HPP_INCLUDED

#include <sanguis/client/systems_unique_ptr.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

sanguis::client::systems_unique_ptr
create_systems(
	fcppt::log::context &,
	boost::program_options::variables_map const &
);

}
}

#endif
