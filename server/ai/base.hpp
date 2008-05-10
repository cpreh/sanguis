#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include "../entities/entity_fwd.hpp"
#include "../../time_type.hpp"
#include <boost/shared_ptr.hpp>

namespace sanguis
{
namespace server
{

namespace ai
{

class base {
public:
	virtual void update(
		time_type,
		entities::container const &) = 0;
	virtual ~base();
};

typedef boost::shared_ptr<base> ai_ptr;

}
}
}

#endif
