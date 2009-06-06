#ifndef SANGUIS_CLIENT_CURSOR_VISIBLE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_VISIBLE_CALLBACK_HPP_INCLUDED

#include "visible_fn.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{
typedef boost::function<visible_fn> visible_callback;
}
}
}

#endif // SANGUIS_CLIENT_CURSOR_VISIBLE_CALLBACK_HPP_INCLUDED
