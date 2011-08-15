#include "scoped.hpp"
#include "object.hpp"
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>

sanguis::client::cursor::scoped::scoped(
	cursor::object &_cursor
)
:
	cursor_(_cursor)
{
	FCPPT_ASSERT_PRE(
		!cursor_.active()
	);

	cursor_.active(
		true
	);
}

sanguis::client::cursor::scoped::~scoped()
{
	FCPPT_ASSERT_ERROR(
		cursor_.active()
	);

	cursor_.active(
		false
	);
}
