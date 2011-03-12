#ifndef SANGUIS_MESSAGES_SHARED_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SHARED_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/shared_ptr.hpp>

namespace sanguis
{
namespace messages
{

typedef fcppt::shared_ptr<base> shared_ptr;

}
}

#endif
