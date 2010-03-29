#ifndef SANGUIS_MAIN_OBJECT_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_MAIN_OBJECT_AUTO_PTR_HPP_INCLUDED

#include "main_object_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{

typedef fcppt::auto_ptr<
	main_object
> main_object_auto_ptr;

}

#endif
