#ifndef SANGUIS_SERVER_LOAD_HPP_INCLUDED
#define SANGUIS_SERVER_LOAD_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sanguis/server/load_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

class load
{
	FCPPT_NONCOPYABLE(
		load
	);
public:
	load();

	~load();

	sanguis::model::cell_size const
	model_dim(
		fcppt::string const &
	) const;
private:
	typedef std::map<
		fcppt::string,
		sanguis::model::cell_size
	> dim_map;

	mutable dim_map dims_;
};

}
}

#endif
