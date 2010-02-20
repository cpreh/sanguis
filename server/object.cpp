#include "object.hpp"
#include <sge/systems/instance.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::server::object::object(
	sge::systems::instance const &sys,
	boost::program_options::variables_map const &vm,
	load::model::context const *const model_context
)
:
	machine_(
		*model_context, // TODO!model_context,
		sys.collision_system(),
		vm["port"].as<net::port_type>()
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

int
sanguis::server::object::run()
{
	// TODO: run the thread here instead!
}

void
sanguis::server::object::mainloop()
{
	
}
