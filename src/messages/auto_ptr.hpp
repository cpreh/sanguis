#ifndef SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <memory>

namespace sanguis
{
namespace messages
{

typedef std::auto_ptr<
	messages::base
> auto_ptr;

}
}

#endif
