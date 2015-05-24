#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/reference_tree.hpp>
#include <sanguis/gui/widget/reference_tree_vector.hpp>
#include <sanguis/gui/widget/tree.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_concat_move.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/tree/level.hpp>
#include <fcppt/container/tree/pre_order.hpp>


sanguis::gui::widget::tree::tree(
	sanguis::gui::context &_context,
	sanguis::gui::widget::reference_tree_vector const &_widgets
)
:
	sanguis::gui::widget::box_container(
		_context,
		sanguis::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::y
	),
	boxes_(
		fcppt::algorithm::map_concat_move<
			sanguis::gui::widget::unique_ptr_vector
		>(
			_widgets,
			[
				&_context
			](
				sanguis::gui::widget::reference_tree const &_tree
			)
			{
				return
					fcppt::algorithm::map<
						sanguis::gui::widget::unique_ptr_vector
					>(
						fcppt::container::tree::pre_order<
							sanguis::gui::widget::reference_tree const
						>(
							_tree
						),
						[
							&_context
						](
							sanguis::gui::widget::reference_tree const &_widget
						)
						{
							class indented_widget
							:
								public sanguis::gui::widget::box_container
							{
								FCPPT_NONCOPYABLE(
									indented_widget
								);
							public:
								indented_widget(
									sge::rucksack::scalar const _indent,
									sanguis::gui::context &_new_context,
									sanguis::gui::widget::base &_new_widget
								)
								:
									sanguis::gui::widget::box_container(
										_new_context,
										sanguis::gui::widget::reference_alignment_vector{
											sanguis::gui::widget::reference_alignment_pair(
												sanguis::gui::widget::reference(
													_new_widget
												),
												sge::rucksack::alignment::left_or_top
											)
										},
										sge::rucksack::axis::x
									),
									padding_{
										sge::rucksack::axis_policy2{
											sge::rucksack::axis_policy{
												sge::rucksack::preferred_size{
													_indent
												}
											},
											sge::rucksack::axis_policy{
												sge::rucksack::minimum_size{
													fcppt::literal<
														sge::rucksack::scalar
													>(
														0
													)
												}
											}
										}
									}
								{
									this->box_layout().push_front_child(
										padding_,
										sge::rucksack::alignment::left_or_top
									);
								}

								~indented_widget()
								{
								}
							private:
								sge::rucksack::widget::dummy padding_;
							};

							return
								fcppt::unique_ptr_to_base<
									sanguis::gui::widget::base
								>(
									fcppt::make_unique_ptr_fcppt<
										indented_widget
									>(
										fcppt::cast::size<
											sge::rucksack::scalar
										>(
											fcppt::cast::to_signed(
												fcppt::container::tree::level(
													_widget
												)
											)
										)
										*
										fcppt::literal<
											sge::rucksack::scalar
										>(
											20
										),
										_context,
										_widget.value().get()
									)
								);
						}
					);
			}
		)
	)
{
	for(
		auto &box
		:
		boxes_
	)
		this->push_back(
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					*box
				),
				sge::rucksack::alignment::left_or_top
			)
		);
}

sanguis::gui::widget::tree::~tree()
{
}
