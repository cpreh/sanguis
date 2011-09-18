#ifndef SANGUIS_LOAD_MODEL_SPLIT_PAIR_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_SPLIT_PAIR_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

typedef std::pair<
	fcppt::string,
	fcppt::string
> split_pair;

}
}
}

#endif
