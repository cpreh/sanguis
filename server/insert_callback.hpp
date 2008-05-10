#ifndef SANGUIS_SERVER_INSERT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_INSERT_CALLBACK_HPP_INCLUDED

#include "entities/entity_fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<entities::entity & (entities::auto_ptr)> insert_callback;

}
}

#endif
