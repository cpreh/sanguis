#ifndef SANGUIS_SERVER_AI_SCOPED_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SCOPED_PTR_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

typedef fcppt::scoped_ptr<
	base
> scoped_ptr;

}
}
}

#endif
