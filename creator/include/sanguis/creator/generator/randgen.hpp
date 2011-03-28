#ifndef SANGUIS_CREATOR_GENERATOR_RANDGEN_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_RANDGEN_HPP_INCLUDED

#include <sanguis/creator/generator/randvalue.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

class randgen
{
	FCPPT_NONCOPYABLE(
		randgen
	);
public:
	SANGUIS_CREATOR_SYMBOL
	explicit randgen(
		generator::seed const &
	);

	SANGUIS_CREATOR_SYMBOL
	~randgen();

	SANGUIS_CREATOR_SYMBOL
	randvalue const
	operator()();
private:
	// TODO:
};

}
}
}

#endif
