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

sanguis::client::cursor::point const
sanguis::client::cursor::object::pos() const
{
	return cursor_->position();
}

sge::input::cursor::object_ptr const
sanguis::client::cursor::object::get() const
{
	return cursor_;
}
