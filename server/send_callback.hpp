#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include "../messages/base.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<
	void (messages::auto_ptr)
> send_callback;

}
}

#endif
