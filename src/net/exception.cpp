#include <sanguis/net/exception.hpp>

sanguis::net::exception::exception(
	fcppt::string const &_message
)
:
	sanguis::exception(
		_message
	)
{
}
