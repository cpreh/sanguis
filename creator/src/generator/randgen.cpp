#include <sanguis/creator/generator/randgen.hpp>

sanguis::creator::generator::randgen::randgen(
	generator::seed const &_seed
)
{
}

sanguis::creator::generator::randgen::~randgen()
{
}

sanguis::creator::generator::randvalue const
sanguis::creator::generator::randgen::operator()()
{
	return generator::randvalue(0); // FIXME!
}
