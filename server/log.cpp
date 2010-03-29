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
		FCPPT_TEXT("server")
	)
);

}

fcppt::log::object &
sanguis::server::log()
{
	return log_;
}
