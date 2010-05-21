#ifndef SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED

#include "pos_callback.hpp"
#include "visible_callback.hpp"
#include <sge/gui/cursor/default.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{

class object
:
	public sge::gui::cursor::default_
{
public:
	object(
		sge::image::multi_loader &,
		sge::renderer::device_ptr
	);

	~object();

	sge::gui::point const
	pos() const;

	void
	pos(
		sge::gui::point const &
	);

	void
	visible(
		bool
	);

	fcppt::signal::auto_connection
	register_pos_callback(
		pos_callback const &
	);

	fcppt::signal::auto_connection
	register_visible_callback(
		visible_callback const &
	);
private:
	typedef fcppt::signal::object<pos_fn> pos_signal_type;
	typedef fcppt::signal::object<visible_fn> visible_signal_type;

	pos_signal_type pos_signal_;
	visible_signal_type visible_signal_;
};

}
}
}

#endif // SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
