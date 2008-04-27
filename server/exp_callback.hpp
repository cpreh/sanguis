#ifndef SANGUIS_SERVER_EXP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_EXP_CALLBACK_HPP_INCLUDED

#include "../messages/types.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<void (messages::exp_type)> exp_callback;

}
}

#endif
