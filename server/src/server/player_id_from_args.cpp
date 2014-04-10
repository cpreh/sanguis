#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_args.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sge/console/arg_list.hpp>
#include <alda/net/id.hpp>
#include <fcppt/extract_from_string_exn.hpp>


sanguis::server::player_id const
sanguis::server::player_id_from_args(
	sge::console::arg_list const &_args
)
{
	return
		sanguis::server::player_id_from_net(
			alda::net::id(
				fcppt::extract_from_string_exn<
					alda::net::id::value_type
				>(
					_args.back()
				)
			)
		);
}
