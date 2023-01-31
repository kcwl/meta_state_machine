#pragma once
#include <msm/front/common_states.hpp>
#include <msm/row_tags.hpp>
#include <msm/common_types.hpp>
#include <exception>
#include <msm/front/states.hpp>

namespace msm
{
	namespace front
	{
		template<typename _Derived, typename _BaseState = default_base_state>
		struct state_machine_def : public msm::front::state_base<_BaseState>
		{
			using flag_list = std::tuple<>;
			using internal_flag_list = std::tuple<>;
			using deferred_events = std::tuple<>;
			using configuration = std::tuple<>;

			using base_all_state = _BaseState;

			template<typename _Source, typename _Event, typename _Target, void(_Derived::* action)(const _Event&)>
			struct a_row
			{
				using row_type_tag = a_row_tag;
				using source_type = _Source;
				using target_type = _Target;
				using event_type = _Event;

				template<typename _Fsm/*, typename _Source, typename _Target, typename _AllState*/>
				static execute_t action_all(_Fsm& fsm, const _Event& evt/*, _Source&, _Target&, _AllState&*/)
				{
					(fsm.*action)(evt);

					return msm::Handle::Handle_True;
				}
			};

			template<typename _Source, typename _Event, typename _Target, void(_Derived::* action)(const _Event&), bool(_Derived::* guard)(const _Event&)>
			struct row
			{
				using row_type_tag = row_tag;
				using source_type = _Source;
				using target_type = _Target;
				using event_type = _Event;

				template<typename _Fsm/*, typename _Source, typename _Target, typename _AllState*/>
				static execute_t action_all(_Fsm& fsm, const _Event& evt/*, _Source&, _Target&, _AllState&*/)
				{
					(fsm.*action)(evt);

					return msm::Handle::Handle_True;
				}

				template<typename _Fsm, typename _Source, typename _Target, typename _AllState>
				static bool guard_all(_Fsm& fsm, const _Event& evt, _Source&, _Target&, _AllState&)
				{
					return (fsm.*guard)(evt);
				}
			};


		protected:
			template<typename _Fsm, typename _Event>
			void on_transition(const _Event&, _Fsm&, int)
			{
				static_assert(false, "some transition error!");
			}

			template<typename _Fsm, typename _Event>
			void exception_caught(const _Event&, _Fsm&, std::exception&)
			{
				//static_assert(false, "exception occure!");
			}
		};
	}
}