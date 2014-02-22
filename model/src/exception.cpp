#include <sanguis/model/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sanguis::model::exception::exception(
	fcppt::string const &_message
)
:
	fcppt::exception(
		FCPPT_TEXT("model: ")
		+
		_message
	)
{
}

sanguis::model::exception::~exception() throw()
{
}
