#ifndef SANGUIS_MESSAGES_SHARED_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SHARED_PTR_HPP_INCLUDED

#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace messages
{

class base;
typedef sge::shared_ptr<base> shared_ptr;

}
}

#endif
