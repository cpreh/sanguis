#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_HOOK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_HOOK_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities
{

using auto_weak_hook =
    boost::intrusive::list_base_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink>>;

}

#endif
