#ifndef SANGUIS_SERVER_LEVEL_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_LEVEL_CALLBACK_HPP_INCLUDED

#include "../messages/types.hpp"
#include "entities/fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<void (entities::player &,messages::level_type)> level_callback;

}
}

#endif
