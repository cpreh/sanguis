#ifndef SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED

#include <sge/sprite/point.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{

typedef boost::function<
	void (sge::sprite::point const &)
> cursor_pos_callback;

}
}

#endif
