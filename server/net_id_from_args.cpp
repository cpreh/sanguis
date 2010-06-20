#include "net_id_from_args.hpp"
#include <fcppt/lexical_cast.hpp>

sanguis::net::id_type
sanguis::server::net_id_from_args(
	sge::console::arg_list const &args_
)
{
	return
		fcppt::lexical_cast<
			net::id_type
		>(
			args_.back()
		);
}
