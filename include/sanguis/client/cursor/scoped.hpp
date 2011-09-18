#ifndef SANGUIS_CLIENT_CURSOR_SCOPED_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_SCOPED_HPP_INCLUDED

#include <sanguis/client/cursor/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{

class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	explicit scoped(
		cursor::object &
	);

	~scoped();
private:
	cursor::object &cursor_;
};

}
}
}

#endif
