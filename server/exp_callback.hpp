#ifndef SANGUIS_SERVER_EXP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_EXP_CALLBACK_HPP_INCLUDED

#include "exp_type.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<
	void (exp_type)
> exp_callback;

}
}

#endif
