#include <sanguis/server/weapons/make_attribute.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string
sanguis::server::weapons::make_attribute(
	fcppt::string const &_name,
	fcppt::string const &_value
)
{
	return
		_name
		+
		FCPPT_TEXT(": ")
		+
		_value;
}
