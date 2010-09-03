#include "create.hpp"
#include "object.hpp"
#include "../args/server_port.hpp"
#include <fcppt/make_unique_ptr.hpp>

sanguis::main_object_unique_ptr
sanguis::server::create(
	sge::systems::instance const &sys,
	boost::program_options::variables_map const &vm,
	load::context_base const &context
)
{
	return
		main_object_unique_ptr(
			fcppt::make_unique_ptr<
				object
			>(
				sys,
				args::server_port(
					vm
				),
				context
			)
		);
}
