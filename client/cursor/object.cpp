#include "object.hpp"
#include <sge/sprite/object_impl.hpp>

sanguis::client::cursor::object::object(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
: 
	default_(
		il,
		rend),
	pos_signal_(),
	visible_signal_()
{
	visible(
		true);
}

sanguis::client::cursor::object::~object()
{}

sge::gui::point const sanguis::client::cursor::object::pos() const
{
	return sge::gui::cursor::default_::pos();
}

void sanguis::client::cursor::object::pos(
	sge::gui::point const &p) 
{
	pos_signal_(
		p);
	sge::gui::cursor::default_::pos(
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

fcppt::signal::auto_connection sanguis::client::cursor::object::register_pos_callback(
	pos_callback const &p)
{
	return pos_signal_.connect(
		p);
}

fcppt::signal::auto_connection sanguis::client::cursor::object::register_visible_callback(
	visible_callback const &p)
{
	return visible_signal_.connect(
		p);
}
