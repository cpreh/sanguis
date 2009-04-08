#ifndef SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED

#include <boost/function.hpp>

namespace sanguis
{
namespace client
{
typedef boost::function<void ()> server_callback;
}
}

#endif // SANGUIS_CLIENT_SERVER_CALLBACK_HPP_INCLUDED
