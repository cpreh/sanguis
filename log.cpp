#include "log.hpp"
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/root.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <sge/cerr.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::root(
			sge::cerr
		)
		.prefix(
			FCPPT_TEXT("sanguis")
		)
		.enabled(
			true
		)
		.level(
			fcppt::log::level::warning
		)
		.create()
	);
	return log_;
}
