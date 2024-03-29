#ifndef SANGUIS_SERVER_ENTITIES_LINK_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_LINK_CONTAINER_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_link_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities
{

using link_container = boost::intrusive::
    list<sanguis::server::entities::auto_weak_link, boost::intrusive::constant_time_size<false>>;

}

#endif
