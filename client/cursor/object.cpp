#include "object.hpp"

sanguis::client::cursor::object::object(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
: 
	default_cursor(
		il,
		rend),
	pos_signal_(),
	visible_signal_()
{
	visible(
		false);
}

sge::gui::point const sanguis::client::cursor::object::pos() const
{
	return sge::gui::default_cursor::pos();
}

void sanguis::client::cursor::object::pos(
	sge::gui::point const &p) 
{
	pos_signal_(
		p);
	default_cursor::pos(
		p);
}

void sanguis::client::cursor::object::visible(
	bool const n)
{
	visible_signal_(
		n);
	mutable_sprite().visible(
		n);
}

sge::signal::auto_connection sanguis::client::cursor::object::register_pos_callback(
	pos_callback const &p)
{
	return pos_signal_.connect(
		p);
}

sge::signal::auto_connection sanguis::client::cursor::object::register_visible_callback(
	visible_callback const &p)
{
	return visible_signal_.connect(
		p);
}
