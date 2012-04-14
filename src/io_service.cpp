#include <sanguis/io_service_callback.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/io_service_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/function/object.hpp>


sanguis::io_service::io_service()
:
	impl_(
		fcppt::make_unique_ptr<
			sanguis::io_service_impl
		>()
	)
{
}

sanguis::io_service::~io_service()
{
}

void
sanguis::io_service::post(
	sanguis::io_service_callback const &_callback
)
{
	impl_->get().post(
		_callback
	);
}

void
sanguis::io_service::run()
{
	impl_->get().run();
}

void
sanguis::io_service::stop()
{
	impl_->get().stop();
}

sanguis::io_service_impl &
sanguis::io_service::impl()
{
	return *impl_;
}
