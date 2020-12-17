#ifndef SANGUIS_IO_SERVICE_HPP_INCLUDED
#define SANGUIS_IO_SERVICE_HPP_INCLUDED

#include <sanguis/io_service_callback.hpp>
#include <sanguis/io_service_fwd.hpp>
#include <sanguis/io_service_impl_fwd.hpp>
#include <sanguis/common/symbol.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{

class io_service
{
	FCPPT_NONMOVABLE(
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

	[[nodiscard]]
	SANGUIS_COMMON_SYMBOL
	alda::net::io_service_wrapper const &
	impl() const;
private:
	using
	impl_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::io_service_impl
	>;

	impl_unique_ptr const impl_;
};

}

#endif
