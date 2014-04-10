#include <sanguis/server/entities/enemies/attribute.hpp>
#include <fcppt/string.hpp>


sanguis::server::entities::enemies::attribute::attribute(
	fcppt::string const &_text
)
:
	text_(
		_text
	)
{
}

fcppt::string const &
sanguis::server::entities::enemies::attribute::text() const
{
	return
		text_;
}
