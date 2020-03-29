#ifndef SANGUIS_COLLISION_LOG_HPP_INCLUDED
#define SANGUIS_COLLISION_LOG_HPP_INCLUDED

#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sanguis
{
namespace collision
{

class log
{
	FCPPT_NONCOPYABLE(
		log
	);
public:
	SANGUIS_COLLISION_SYMBOL
	explicit
	log(
		fcppt::log::context_reference
	);

	SANGUIS_COLLISION_SYMBOL
	~log();

	fcppt::log::object &
	body_log() const;
private:
	mutable fcppt::log::object body_log_;
};

}
}

#endif
