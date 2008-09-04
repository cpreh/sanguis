#ifndef SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED

#include "../messages/base.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{

typedef boost::function<
	void (messages::auto_ptr)
> send_callback;

}
}

#endif
