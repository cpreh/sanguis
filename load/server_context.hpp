#ifndef SANGUIS_LOAD_SERVER_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_SERVER_CONTEXT_HPP_INCLUDED

#include "context_base.hpp"
#include <sge/renderer/dim2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <map>

namespace sanguis
{
namespace load
{

class server_context
:
	public context_base
{
	FCPPT_NONCOPYABLE(server_context)
public:
	server_context();

	~server_context();
private:
	sge::renderer::dim2 const
	model_dim(
		fcppt::string const &
	) const;

	typedef std::map<
		fcppt::string,
		sge::renderer::dim2
	> dim_map;

	mutable dim_map dims_;
};

}
}

#endif
