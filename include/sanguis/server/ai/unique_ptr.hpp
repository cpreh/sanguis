#ifndef SANGUIS_SERVER_AI_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

typedef std::unique_ptr<
	sanguis::server::ai::base
> unique_ptr;

}
}
}

#endif
