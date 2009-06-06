#ifndef SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED

#include "pos_fn.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{
typedef boost::function<pos_fn> pos_callback;
}
}
}

#endif // SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED
