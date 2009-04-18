#include "cursor.hpp"

sanguis::client::cursor::cursor(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
: 
	default_cursor(
		il,
		rend)
{
	visible(false);
}

void sanguis::client::cursor::pos(sge::gui::point const &) {}

sge::gui::point const sanguis::client::cursor::pos() const 
{
	return default_cursor::pos();
}

void sanguis::client::cursor::real_pos(
	sge::gui::point const &p) 
{
	default_cursor::pos(p);
}

void sanguis::client::cursor::visible(
	bool const n)
{
	mutable_sprite().visible(n);
}

sanguis::client::cursor::~cursor() {}
