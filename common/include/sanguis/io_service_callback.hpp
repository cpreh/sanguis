#ifndef SANGUIS_IO_SERVICE_CALLBACK_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_CALLBACK_HPP_INCLUDED

#include <fcppt/function_impl.hpp>


namespace sanguis
{

typedef
fcppt::function<
	void ()
>
io_service_callback;

}

#endif
