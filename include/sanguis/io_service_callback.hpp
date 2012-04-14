#ifndef SANGUIS_IO_SERVICE_CALLBACK_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_CALLBACK_HPP_INCLUDED

#include <fcppt/function/object_fwd.hpp>


namespace sanguis
{

typedef fcppt::function::object<
	void ()
> io_service_callback;

}

#endif
