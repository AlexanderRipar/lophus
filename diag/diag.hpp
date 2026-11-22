#ifndef DIAG_INCLUDE_GUARD
#define DIAG_INCLUDE_GUARD

#include "../core/core.hpp"
#include "../infra/print/print.hpp"

namespace diag
{
	s64 print_ast(PrintSinkHandle sink, CoreData* core, AstNode* root) noexcept;

	s64 print_type(PrintSinkHandle sink, CoreData* core, TypeId type_id) noexcept;

	s64 print_code2(PrintSinkHandle sink, CoreData* core, const Code2Block* header) noexcept;

	template<typename Sink, typename... Inserts>
	s64 print_header(Sink sink, const char8* format, Inserts... inserts) noexcept
	{
		const s64 begin_written = print(sink, "### ");

		if (begin_written < 0)
			return -1;

		const s64 message_written = print(sink, format, inserts...);

		if (message_written < 0)
			return -1;

		const s64 end_written = print(sink, " ###\n");

		if (end_written < 0)
			return -1;

		return begin_written + message_written + end_written;
	}
}

#endif // DIAG_INCLUDE_GUARD
