#include "log.hpp"
#include "log_context.hpp"
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/root.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sanguis::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::root(
			fcppt::io::cerr
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
		.context(
			log_context())
		.create()
	);
	return log_;
}
