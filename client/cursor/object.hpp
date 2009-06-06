#ifndef SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED

#include "pos_callback.hpp"
#include "visible_callback.hpp"
#include <sge/gui/default_cursor.hpp>
#include <sge/signal/object.hpp>
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{
class object : public sge::gui::default_cursor
{
public:
	object(
		sge::image::loader_ptr,
		sge::renderer::device_ptr);
	sge::gui::point const pos() const;
	void pos(
		sge::gui::point const &);
	void visible(
		bool);
	sge::signal::auto_connection register_pos_callback(
		pos_callback const &);
	sge::signal::auto_connection register_visible_callback(
		visible_callback const &);
private:
	typedef sge::signal::object<pos_fn> pos_signal_type;
	typedef sge::signal::object<visible_fn> visible_signal_type;

	pos_signal_type pos_signal_;
	visible_signal_type visible_signal_;
};
}
}
}

#endif // SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
