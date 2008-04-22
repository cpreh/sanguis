#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include "../messages/fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

// TODO: this should use an auto_ptr
typedef boost::function<void (messages::base *)> send_callback;

}
}

#endif
