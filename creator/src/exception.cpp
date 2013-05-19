#include <sanguis/creator/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sanguis::creator::exception::exception(
	fcppt::string const &_message
)
:
	fcppt::exception(
		FCPPT_TEXT("creator: ")
		+
		_message
	)
{
}

sanguis::creator::exception::~exception() throw()
{
}
