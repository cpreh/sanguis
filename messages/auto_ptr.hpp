#ifndef SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace messages
{

class base;
typedef sge::auto_ptr<base> auto_ptr;

}
}

#endif
