#ifndef SANGUIS_SERVER_TYPES_HPP_INCLUDED
#define SANGUIS_SERVER_TYPES_HPP_INCLUDED

#include "../messages/types.hpp"

namespace sanguis
{
namespace server
{

typedef messages::space_unit space_unit;
typedef messages::pos_type   pos_type;
typedef messages::dim_type   dim_type;
typedef space_unit           health_type;

}
}

#endif
