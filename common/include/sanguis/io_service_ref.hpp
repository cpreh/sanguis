#ifndef SANGUIS_IO_SERVICE_REF_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_REF_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{

using
io_service_ref
=
fcppt::reference<
	sanguis::io_service
>;

}

#endif
