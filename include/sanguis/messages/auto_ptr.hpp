#ifndef SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef std::auto_ptr<
	messages::base
> auto_ptr;

}
}

#endif
