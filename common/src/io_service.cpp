#include <sanguis/io_service.hpp>
#include <sanguis/io_service_callback.hpp>
#include <sanguis/io_service_impl.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/post.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::io_service::io_service() : impl_(fcppt::make_unique_ptr<sanguis::io_service_impl>()) {}

sanguis::io_service::~io_service() = default;

void sanguis::io_service::post( // NOLINT(readability-make-member-function-const)
    sanguis::io_service_callback const &_callback)
{
  boost::asio::post(this->impl().get(), _callback);
}

void sanguis::io_service::run() // NOLINT(readability-make-member-function-const)
{
  this->impl().get().run();
}

void sanguis::io_service::stop() // NOLINT(readability-make-member-function-const)
{
  this->impl().get().stop();
}

alda::net::io_service_wrapper const &sanguis::io_service::impl() const { return impl_->get(); }
