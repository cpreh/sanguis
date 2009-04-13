#include "cursor.hpp"

sanguis::client::cursor::cursor(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
: 
	default_cursor(
		il,
		rend)
{
	mutable_sprite().visible(false);
}

sanguis::client::cursor::~cursor() {}
