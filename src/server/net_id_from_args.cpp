#include "net_id_from_args.hpp"
#include <fcppt/lexical_cast.hpp>

sanguis::net::id
sanguis::server::net_id_from_args(
	sge::console::arg_list const &_args
)
{
	return
		fcppt::lexical_cast<
			net::id
		>(
			_args.back()
		);
}
