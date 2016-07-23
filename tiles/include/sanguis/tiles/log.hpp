#ifndef SANGUIS_TILES_LOG_HPP_INCLUDED
#define SANGUIS_TILES_LOG_HPP_INCLUDED

#include <sanguis/tiles/log_fwd.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sanguis
{
namespace tiles
{

class log
{
	FCPPT_NONCOPYABLE(
		log
	);
public:
	SANGUIS_TILES_SYMBOL
	explicit
	log(
		fcppt::log::context &
	);

	SANGUIS_TILES_SYMBOL
	~log();

	fcppt::log::object &
	main_log() const;
private:
	mutable fcppt::log::object main_log_;
};

}
}

#endif
