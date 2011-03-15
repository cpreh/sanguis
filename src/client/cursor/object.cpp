#include "object.hpp"
#include <sge/input/cursor/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::client::cursor::object::object(
	sge::input::cursor::object_ptr const _cursor
)
: 
	cursor_(_cursor)
{
}

sanguis::client::cursor::object::~object()
{
}

sge::input::cursor::position const
sanguis::client::cursor::object::position() const
{
	return cursor_->position();
}
