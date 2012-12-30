#ifndef SANGUIS_IO_SERVICE_CALLBACK_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_CALLBACK_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

typedef std::function<
	void ()
> io_service_callback;

}

#endif
