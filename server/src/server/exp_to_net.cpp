#include <sanguis/messages/types/exp.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/exp_to_net.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


sanguis::messages::types::exp
sanguis::server::exp_to_net(
	sanguis::server::exp const _exp
)
{
	return
		fcppt::cast::to_unsigned(
			fcppt::cast::float_to_int<
				std::make_signed<
					sanguis::messages::types::exp
				>::type
			>(
				_exp.get()
			)
		);
}
