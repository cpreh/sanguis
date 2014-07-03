#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/hover/create.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/variant/apply_unary.hpp>


sanguis::client::draw2d::scene::hover::base_unique_ptr
sanguis::client::draw2d::scene::hover::create(
	sanguis::client::draw2d::scene::hover::parameters const &_parameters,
	sanguis::client::draw2d::entities::hover::info const &_info
)
{
	class visitor
	{
		FCPPT_NONASSIGNABLE(
			visitor
		);
	public:
		explicit
		visitor(
			sanguis::client::draw2d::scene::hover::parameters const &_parameters
		)
		:
			parameters_(
				_parameters
			)
		{
		}

		typedef
		sanguis::client::draw2d::scene::hover::base_unique_ptr
		result_type;

		result_type
		operator()(
			sanguis::client::draw2d::entities::hover::name const &_name
		) const
		{
			return
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::scene::hover::name
				>(
					parameters_,
					_name
				);
		}
	private:
		sanguis::client::draw2d::scene::hover::parameters const &parameters_;
	};

	return
		fcppt::variant::apply_unary(
			visitor(
				_parameters
			),
			_info.get()
		);
}
