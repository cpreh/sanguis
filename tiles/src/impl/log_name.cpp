#include <sanguis/tiles/impl/log_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/name.hpp>


fcppt::log::name
sanguis::tiles::impl::log_name()
{
	return
		fcppt::log::name{
			FCPPT_TEXT("tiles")
		};
}
