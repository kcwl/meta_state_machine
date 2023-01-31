#pragma once

namespace msm
{
	namespace front
	{
		struct default_base_state
		{
			~default_base_state()
			{

			}
		};

		struct polymorphic_state
		{
			virtual ~polymorphic_state()
			{

			}
		};

		template<typename _Userbase>
		struct state_base : public _Userbase
		{
			using user_state_base = _Userbase;

			template<typename _Event, typename _Fsm>
			void on_entry(_Event&&, _Fsm&) {}

			template<typename _Event, typename _Fsm>
			void on_exit(_Event&&, _Fsm&) {}
		};
	}
}