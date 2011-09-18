#ifndef SANGUIS_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_HPP_INCLUDED

#include <sanguis/load/context_base.hpp>
#include <sanguis/main_object_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{

sanguis::main_object_unique_ptr
create(
	boost::program_options::variables_map const &,
	load::context_base const &
);

}
}

#endif
