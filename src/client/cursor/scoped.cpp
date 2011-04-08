#include "scoped.hpp"
#include "object.hpp"
#include <fcppt/assert.hpp>

sanguis::client::cursor::scoped::scoped(
	cursor::object &_cursor
)
:
	cursor_(_cursor)
{
	FCPPT_ASSERT(
		!cursor_.active()
	);

	cursor_.active(
		true
	);
}

sanguis::client::cursor::scoped::~scoped()
{
	FCPPT_ASSERT(
		cursor_.active()
	);

	cursor_.active(
		false
	);
}
