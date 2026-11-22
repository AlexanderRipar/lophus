#ifndef PRINT_INCLUDE_GUARD
#define PRINT_INCLUDE_GUARD

#include "../types.hpp"
#include "../opt.hpp"
#include "../range.hpp"
#include "../minos/minos.hpp"

struct PrintState;

using print_sink_write_func = s64 (*) (void* sink_attach, Range<char8> buffer, bool flush) noexcept;

struct PrintSink
{
	print_sink_write_func write_func;

	alignas(8) byte attach[24];
};

using PrintSinkHandle = PrintSink*;

enum class PrintAlignment : u8
{
	None,
	Left,
	Right,
	Center,
};

struct PrintSpec
{
	PrintAlignment alignment;

	char8 align_padding_char;

	u64 align_frame_size;

	Maybe<const char8*> extended_spec;
};

struct PrintInsert;

using print_format_func = bool (*) (PrintState* state, const void* insert_attach, PrintSpec spec) noexcept;

struct PrintInsert
{
	print_format_func format_func;

	alignas(8) byte attach[24];
};

PrintInsert print_make_insert(u8) noexcept;
PrintInsert print_make_insert(u16) noexcept;
PrintInsert print_make_insert(u32) noexcept;
PrintInsert print_make_insert(u64) noexcept;
PrintInsert print_make_insert(s8) noexcept;
PrintInsert print_make_insert(s16) noexcept;
PrintInsert print_make_insert(s32) noexcept;
PrintInsert print_make_insert(s64) noexcept;
PrintInsert print_make_insert(f32) noexcept;
PrintInsert print_make_insert(f64) noexcept;
PrintInsert print_make_insert(bool) noexcept;
PrintInsert print_make_insert(const char8*) noexcept;
PrintInsert print_make_insert(Range<char8>) noexcept;

PrintSink print_make_sink(minos::FileHandle file) noexcept;
PrintSink print_make_sink(MutRange<char8> buffer) noexcept;

PrintSink print_make_buffered_sink(PrintSinkHandle target, MutRange<char8> buffer) noexcept;



s64 print_flush_sink(PrintSinkHandle sink) noexcept;



s64 vprint(PrintSinkHandle sink, bool flush, Range<char8> format, Range<PrintInsert> inserts) noexcept;

template<typename... Inserts>
s64 print(PrintSinkHandle sink, Range<char8> format, Inserts... inserts) noexcept
{
	if constexpr (sizeof...(inserts) != 0)
	{
		PrintInsert erased_inserts[] = { print_make_insert(inserts)... };

		return vprint(sink, true, format, Range{ erased_inserts });
	}
	else
	{
		return vprint(sink, true, format, {});
	}
}

template<typename... Inserts>
s64 print(PrintSinkHandle sink, const char8* format, Inserts... inserts) noexcept
{
	return print(sink, range::from_cstring(format), inserts...);
}

template<typename Sink, typename... Inserts>
s64 print(Sink sink, Range<char8> format, Inserts... inserts) noexcept
{
	PrintSink print_sink = print_make_sink(sink);

	return print(&print_sink, format, inserts...);
}

template<typename Sink, typename... Inserts>
s64 print(Sink sink, const char8* format, Inserts... inserts) noexcept
{
	PrintSink print_sink = print_make_sink(sink);

	return print(&print_sink, range::from_cstring(format), inserts...);
}

template<typename... Inserts>
s64 print_noflush(PrintSinkHandle sink, Range<char8> format, Inserts... inserts) noexcept
{
	if constexpr (sizeof...(inserts) != 0)
	{
		PrintInsert erased_inserts[] = { print_make_insert(inserts)... };

		return vprint(sink, false, format, Range{ erased_inserts });
	}
	else
	{
		return vprint(sink, false, format, {});
	}
}

template<typename... Inserts>
s64 print_noflush(PrintSinkHandle sink, const char8* format, Inserts... inserts) noexcept
{
	return print_noflush(sink, range::from_cstring(format), inserts...);
}

template<typename Sink, typename... Inserts>
s64 print_noflush(Sink sink, Range<char8> format, Inserts... inserts) noexcept
{
	PrintSink print_sink = print_make_sink(sink);

	return print_noflush(&print_sink, format, inserts...);
}

template<typename Sink, typename... Inserts>
s64 print_noflush(Sink sink, const char8* format, Inserts... inserts) noexcept
{
	PrintSink print_sink = print_make_sink(sink);

	return print_noflush(&print_sink, range::from_cstring(format), inserts...);
}

#endif // PRINT_INCLUDE_GUARD
