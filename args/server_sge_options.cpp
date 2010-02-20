#include "server_sge_options.hpp"

sge::systems::list const
sanguis::args::server_sge_options(
	boost::program_options::variables_map const &
)
{
	return
		sge::systems::list()
		(sge::systems::parameterless::collision_system);
}
