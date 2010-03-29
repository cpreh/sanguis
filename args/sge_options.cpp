#include "sge_options.hpp"
#include "server_only.hpp"
#include "server_sge_options.hpp"
#include "client_sge_options.hpp"

sge::systems::list const
sanguis::args::sge_options(
	boost::program_options::variables_map const &vm
)
{
	return
		server_only(
			vm
		)
		?
			client_sge_options(
				vm
			)
		:
			// TODO: we might want a client only mode, too
			client_sge_options(
				vm
			)
			.append(
				server_sge_options(
					vm
				)
			);
}
