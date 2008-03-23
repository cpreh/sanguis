#ifndef SANGUIS_MISSING_HANDLER_HPP_INCLUDED
#define SANGUIS_MISSING_HANDLER_HPP_INCLUDED

#include "messages/fwd.hpp"
#include <boost/statechart/result.hpp>

namespace sanguis
{

boost::statechart::result missing_handler(const messages::base& b);

}

#endif
