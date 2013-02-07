#ifndef SANGUIS_LOAD_SERVER_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_SERVER_CONTEXT_HPP_INCLUDED

#include <sanguis/load/server_context_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{

class server_context
{
	FCPPT_NONCOPYABLE(
		server_context
	);
public:
	server_context();

	~server_context();

	sge::renderer::dim2 const
	model_dim(
		fcppt::string const &
	) const;
private:
	typedef std::map<
		fcppt::string,
		sge::renderer::dim2
	> dim_map;

	mutable dim_map dims_;
};

}
}

#endif
