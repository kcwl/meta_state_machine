#pragma once


namespace msm
{
	struct a_row_tag {};
	struct g_row_tag {};
	struct _row_tag {};
	struct row_tag {};

	struct a_irow_tag {};
	struct g_irow_tag {};
	struct _irow_tag {};
	struct irow_tag {};

	struct sm_a_i_row_tag {};
	struct sm_g_i_row_tag {};
	struct sm__i_row_tag {};
	struct sm_i_row_tag {};

	struct terminate_flag
	{
		using non_forwarding_flag = int;
		using event_blocking_flag = int;
	};

	struct interrupted_flag
	{
		using non_forwarding_flag = int;
		using event_blocking_flag = int;
	};

	template<typename _EndEvent>
	struct end_interrupt_flag
	{
		using non_forwarding_flag = int;
	};
}