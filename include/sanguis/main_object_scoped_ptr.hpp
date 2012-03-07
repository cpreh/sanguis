#ifndef SANGUIS_MAIN_OBJECT_SCOPED_PTR_HPP_INCLUDED
#define SANGUIS_MAIN_OBJECT_SCOPED_PTR_HPP_INCLUDED

#include <sanguis/main_object_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{

typedef fcppt::scoped_ptr<
	sanguis::main_object
> main_object_scoped_ptr;

}

#endif
