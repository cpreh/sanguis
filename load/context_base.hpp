#ifndef SANGUIS_LOAD_CONTEXT_BASE_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_BASE_HPP_INCLUDED

#include "context_base_fwd.hpp"
#include <sge/renderer/dim2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace load
{

class context_base
{
	FCPPT_NONCOPYABLE(context_base)
protected:
	context_base();
public:
	virtual ~context_base();

	virtual sge::renderer::dim2 const
	model_dim(
		fcppt::string const &
	) const = 0;
};

}
}

#endif
