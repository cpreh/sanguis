#ifndef SANGUIS_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_HPP_INCLUDED

#include "../load/model/context_fwd.hpp"
#include "../main_object_auto_ptr.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace server
{

main_object_auto_ptr
create(
	sge::systems::instance const &,
	boost::program_options::variables_map const &,
	load::model::context const *
);

}
}

#endif
