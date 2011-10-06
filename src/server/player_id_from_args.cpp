#include <sanguis/server/player_id_from_args.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <fcppt/extract_from_string_exn.hpp>

sanguis::server::player_id const
sanguis::server::player_id_from_args(
	sge::console::arg_list const &_args
)
{
	return
		server::player_id_from_net(
			fcppt::extract_from_string_exn<
				net::id
			>(
				_args.back()
			)
		);
}
