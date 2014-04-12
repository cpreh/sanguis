#ifndef SANGUIS_IO_SERVICE_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_HPP_INCLUDED

#include <sanguis/io_service_callback.hpp>
#include <sanguis/io_service_fwd.hpp>
#include <sanguis/io_service_impl_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

class io_service
{
	FCPPT_NONCOPYABLE(
		io_service
	);
public:
	SANGUIS_COMMON_SYMBOL
	io_service();

	SANGUIS_COMMON_SYMBOL
	~io_service();

	SANGUIS_COMMON_SYMBOL
	void
	post(
		sanguis::io_service_callback const &
	);

	SANGUIS_COMMON_SYMBOL
	void
	run();

	SANGUIS_COMMON_SYMBOL
	void
	stop();

	SANGUIS_COMMON_SYMBOL
	alda::net::io_service_wrapper const &
	impl() const;
private:
	typedef
	std::unique_ptr<
		sanguis::io_service_impl
	>
	impl_unique_ptr;

	impl_unique_ptr const impl_;
};

}

#endif
