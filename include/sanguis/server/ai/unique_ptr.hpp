#ifndef SANGUIS_SERVER_AI_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

typedef fcppt::unique_ptr<
	base
> unique_ptr;

}
}
}

#endif
