#include "object.hpp"

sanguis::server::object::object(
	sge::systems::instance &sys,
	boost::program_options::variables_map const &vm,
	load::model::context const &model_context
)
:
	machine_(
		model_context,
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

void
sanguis::server::object::mainloop()
{
	
}
