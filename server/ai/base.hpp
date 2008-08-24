#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include "../entities/entity_fwd.hpp"
#include "../entities/enemies/fwd.hpp"
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
	virtual void update(
		entities::enemies::enemy &me,
		time_type,
		entities::container const &) = 0;
	virtual ~base();
};

typedef boost::shared_ptr<base> ai_ptr;

}
}
}

#endif
