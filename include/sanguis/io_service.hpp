#ifndef SANGUIS_IO_SERVICE_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_HPP_INCLUDED

#include <sanguis/io_service_callback.hpp>
#include <sanguis/io_service_fwd.hpp>
#include <sanguis/io_service_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sanguis
{

class io_service
{
	FCPPT_NONCOPYABLE(
		io_service
	);
public:
	io_service();

	~io_service();

	void
	post(
		sanguis::io_service_callback const &
	);

	void
	run();

	void
	stop();

	sanguis::io_service_impl &
	impl();
private:
	typedef fcppt::scoped_ptr<
		sanguis::io_service_impl
	> impl_scoped_ptr;

	impl_scoped_ptr const impl_;
};

}

#endif
