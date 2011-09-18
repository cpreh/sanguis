#ifndef SANGUIS_MAIN_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_MAIN_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/main_object_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{

typedef fcppt::unique_ptr<
	sanguis::main_object
> main_object_unique_ptr;

}

#endif
