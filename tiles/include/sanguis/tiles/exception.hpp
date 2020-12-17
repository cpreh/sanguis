#ifndef SANGUIS_TILES_EXCEPTION_HPP_INCLUDED
#define SANGUIS_TILES_EXCEPTION_HPP_INCLUDED

#include <sanguis/tiles/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/symbol/class.hpp>


namespace sanguis
{
namespace tiles
{

class FCPPT_SYMBOL_CLASS exception
:
	public fcppt::exception
{
public:
	SANGUIS_TILES_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	SANGUIS_TILES_SYMBOL
	exception(
		exception &&
	)
	noexcept;

	SANGUIS_TILES_SYMBOL
	exception(
		exception const &
	);

	SANGUIS_TILES_SYMBOL
	exception &
	operator=(
		exception &&
	)
	noexcept;

	SANGUIS_TILES_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SANGUIS_TILES_SYMBOL
	~exception() noexcept
	override;
};

}
}

#endif
