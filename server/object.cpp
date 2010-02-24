#include "object.hpp"
#include "../args/server_port.hpp"
#include <sge/systems/instance.hpp>
#include <fcppt/tr1/functional.hpp>
#include <cstdlib>

sanguis::server::object::object(
	sge::systems::instance const &sys,
	boost::program_options::variables_map const &vm,
	load::context_base const &load_context
)
:
	machine_(
		load_context,
		sys.collision_system(),
		args::server_port(
			vm
		)
	),
	server_thread_(
		std::tr1::bind(
			&object::mainloop,
			this
		)
	)
{}

sanguis::server::object::~object()
{}

void
sanguis::server::object::quit()
{
	// TODO
}

int
sanguis::server::object::run()
{
	server_thread_.join();

	return EXIT_SUCCESS;
}

void
sanguis::server::object::mainloop()
{
	// TODO	
}
