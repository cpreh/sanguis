#ifndef SANGUIS_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_HPP_INCLUDED

#include "../load/context_base.hpp"
#include "../main_object_unique_ptr.hpp"
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace server
{

main_object_unique_ptr
create(
	boost::program_options::variables_map const &,
	load::context_base const &
);

}
}

#endif
