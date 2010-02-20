#ifndef SANGUIS_CLIENT_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_CREATE_HPP_INCLUDED

#include "../main_object_auto_ptr.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace client
{

main_object_auto_ptr
create(
	sge::systems::instance const &,
	boost::program_options::variables_map const &
);

}
}

#endif
