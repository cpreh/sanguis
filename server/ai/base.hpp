#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include "../entities/entity_fwd.hpp"
#include "../../time_type.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace server
{

namespace ai
{

class base : boost::noncopyable {
public:
	virtual void bind(
		entities::entity_with_weapon &me) = 0;
	
	virtual void update(
		time_type,
		entities::container &) = 0;
	
	virtual ~base();
};

typedef boost::shared_ptr<base> ai_ptr;

}
}
}

#endif
