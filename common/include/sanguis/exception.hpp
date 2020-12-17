#ifndef SANGUIS_EXCEPTION_HPP_INCLUDED
#define SANGUIS_EXCEPTION_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/symbol/class.hpp>


namespace sanguis
{

class FCPPT_SYMBOL_CLASS exception
:
	public fcppt::exception
{
public:
	SANGUIS_COMMON_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	SANGUIS_COMMON_SYMBOL
	explicit
	exception(
		fcppt::assert_::information const &
	);

	SANGUIS_COMMON_SYMBOL
	exception(
		exception &&
	)
	noexcept;

	SANGUIS_COMMON_SYMBOL
	exception(
		exception const &
	);

	SANGUIS_COMMON_SYMBOL
	exception &
	operator=(
		exception &&
	)
	noexcept;

	SANGUIS_COMMON_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SANGUIS_COMMON_SYMBOL
	~exception() noexcept
	override;
};

}

#endif
