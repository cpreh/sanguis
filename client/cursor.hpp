#ifndef SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_HPP_INCLUDED

#include <sge/gui/default_cursor.hpp>
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace client
{
class cursor : public sge::gui::default_cursor
{
public:
	cursor(
		sge::image::loader_ptr,
		sge::renderer::device_ptr);
	void pos(sge::gui::point const &);
	sge::gui::point const pos() const;
	void real_pos(sge::gui::point const &);
	void visible(bool);
	~cursor();
};
typedef sge::shared_ptr<sanguis::client::cursor> cursor_ptr;
}
}

#endif // SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
