#ifndef SANGUIS_MAIN_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_MAIN_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include "main_object_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{

typedef fcppt::unique_ptr<
	main_object
> main_object_unique_ptr;

}

#endif
