#ifndef SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED

#include "point.hpp"
#include <sge/input/cursor/object_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit object(
		sge::input::cursor::object_ptr
	);

	~object();

	cursor::point const
	pos() const;

	sge::input::cursor::object_ptr const
	get() const;
private:
	sge::input::cursor::object_ptr const cursor_;
};

}
}
}

#endif // SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
