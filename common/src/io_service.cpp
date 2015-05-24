#include <sanguis/io_service.hpp>
#include <sanguis/io_service_callback.hpp>
#include <sanguis/io_service_impl.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>


sanguis::io_service::io_service()
:
	impl_(
		fcppt::make_unique_ptr_fcppt<
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
	this->impl().get().post(
		_callback
	);
}

void
sanguis::io_service::run()
{
	this->impl().get().run();
}

void
sanguis::io_service::stop()
{
	this->impl().get().stop();
}

alda::net::io_service_wrapper const &
sanguis::io_service::impl() const
{
	return
		impl_->get();
}
