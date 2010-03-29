#include "log.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::log::object log_(
	fcppt::log::parameters::inherited(
		sanguis::log(),
		FCPPT_TEXT("net")
	)
);

}

fcppt::log::object &
sanguis::net::log()
{
	return log_;
}
