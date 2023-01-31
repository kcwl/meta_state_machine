#pragma once
#include <type_traits>
#include <msm/front/common_states.hpp>
#include <msm/row_tags.hpp>

namespace msm
{
	namespace front
	{
		template<typename _Base = default_base_state>
		struct state : public msm::front::state_base<_Base>
		{
			using flag_list = std::tuple<>;
			using internal_flag_list = std::tuple<>;
			using deferred_events = std::tuple<>;
		};

		template<typename _Base = default_base_state>
		struct terminate_state : public msm::front::state_base<_Base>
		{
			using flag_list = std::tuple<>;
			using internal_flag_list = std::tuple<msm::interrupted_flag>;
			using deferred_events = std::tuple<>;
		};

		template<int Index = -1>
		struct explicit_entry
		{
			using explicit_entry_state = int;

			constexpr static int zone_index = Index;
		};

		template<int Index = -1, typename _Base = default_base_state>
		struct entry_pseudo_state : public msm::front::state_base<_Base>
		{
			using pseudo_entry = int;
			constexpr static int zone_index = Index;
			using flag_list = std::tuple<>;
			using internal_flag_list = std::tuple<>;
			using deferred_events = std::tuple<>;
		};

		template<typename _Event, class _Base = default_base_state>
		struct exit_pseudo_state : public msm::front::state_base<_Base>
		{
			using event_type = _Event;
			using base_type = _Base;
			using pseudo_exit = int;

			using flag_list = std::tuple<>;
			using internal_flag_list = std::tuple<>;
			using deferred_events = std::tuple<>;
		};
	}
}