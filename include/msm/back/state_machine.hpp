#pragma once
#include <msm/common_types.hpp>
#include <type_traits>
#include <exception>
#include <msm/back/transition_table.hpp>
#include <msm/row_tags.hpp>

namespace msm
{
	namespace back
	{
		template<typename _Ty>
		class state_machine : public _Ty
		{
			template<typename _Row>
			struct a_row_
			{
				using current_state_type = int;
				using next_state_type = int;
				using transition_event_type = typename _Row::event_type;

				static execute_t execute(_Ty& fsm, int region_index, int state, const transition_event_type& evt)
				{
					return _Row::action_all(fsm, evt);
				}
			};

			template<typename _Row>
			struct g_row_
			{
				using current_state_type = int;
				using next_state_type = int;
				using transition_event_type = typename _Row::event_type;

				static bool check_guard(state_machine& fsm, const transition_event_type& evt)
				{
					return _Row::guard_call(fsm, evt);
				}

				static execute_t execute(state_machine& fsm, int region_index, int state, const transition_event_type& evt)
				{
					if (!check_guard(fsm, evt))
					{
						return execute_t::Handle_Guard_Reject;
					}

					return _Row::action_all(fsm, evt);
				}
			};

			template<typename _Tag, typename _Transition, typename _State>
			struct create_backend {};

			template<typename _Transition, typename _State>
			struct create_backend<a_row_tag, _Transition, _State>
			{
				using type = a_row_<_Transition>;
			};

			template<typename _Transition, typename _State>
			struct create_backend<g_row_tag, _Transition, _State>
			{
				using type = g_row_<_Transition>;
			};

			template<typename _Transition, class _State = void>
			struct make_row_tag
			{
				using type = typename create_backend<typename _Transition::row_type_tag, _Transition, _State>::type;
			};

		public:
			template<typename _Event>
			execute_t process_event(const _Event& evt)
			{
				return this->do_process_helper<_Event>(evt);
			}

		private:
			template<typename _State, typename _Event>
			execute_t do_process_helper(const _Event& evt)
			{
				std::exception e;

				try
				{
					return this->do_process_event(evt);
				}
				catch (std::exception& e)
				{
					this->exception_caught(evt, *this, e);
				}

				return Handle::Handle_True;
			}

			template<typename _Event>
			execute_t do_process_event(const _Event& evt)
			{
				execute_t result = Handle::Handle_False;

				region_processing_helper<_Event> helper(this, result);
				helper.process(evt);

				return result;
			}

			template<typename _State, typename _Enable = void>
			struct region_processing_helper
			{
				region_processing_helper(state_machine* self, execute_t& handle)
					: self_(self)
					, handle_(handle) {}

				template<typename _Event>
				void process(const _Event& evt)
				{
					using event_type = std::remove_cvref_t<_Event>;

					using row_type = typename find_by<event_type, typename _Ty::transition_table::type>::type;

					using state_source_type = typename row_type::source_type;
					using state_target_type = typename row_type::target_type;

					using row_execute_type = typename make_row_tag<row_type>::type;

					row_execute_type::template execute(*self_, 1, 1, evt);
				}

				state_machine* self_;
				execute_t& handle_;
			};
		};
	}
}