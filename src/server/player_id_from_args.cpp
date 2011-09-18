#include <sanguis/server/player_id_from_args.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <fcppt/lexical_cast.hpp>

sanguis::server::player_id const
sanguis::server::player_id_from_args(
	sge::console::arg_list const &_args
)
{
	return
		server::player_id_from_net(
			fcppt::lexical_cast<
				net::id
			>(
				_args.back()
			)
		);
}
