#include "core.hpp"
#include "structure.hpp"

#include "../infra/types.hpp"
#include "../infra/panic.hpp"
#include "../infra/range.hpp"
#include "../infra/inplace_sort.hpp"
#include "../diag/diag.hpp"

bool comp_heap_validate_config(const Config* config, PrintSink sink) noexcept;

bool ast_pool_validate_config(const Config* config, PrintSink sink) noexcept;

bool error_sink_validate_config(const Config* config, PrintSink sink) noexcept;

bool identifier_pool_validate_config(const Config* config, PrintSink sink) noexcept;

bool lexical_analyser_validate_config(const Config* config, PrintSink sink) noexcept;

bool parser_validate_config(const Config* config, PrintSink sink) noexcept;

bool source_reader_validate_config(const Config* config, PrintSink sink) noexcept;

bool type_pool_validate_config(const Config* config, PrintSink sink) noexcept;

bool temp_stack_validate_config(const Config* config, PrintSink sink) noexcept;

bool code2_validate_config(const Config* config, PrintSink sink) noexcept;



MemoryRequirements comp_heap_memory_requirements(const Config* config) noexcept;

MemoryRequirements ast_pool_memory_requirements(const Config* config) noexcept;

MemoryRequirements error_sink_memory_requirements(const Config* config) noexcept;

MemoryRequirements identifier_pool_memory_requirements(const Config* config) noexcept;

MemoryRequirements lexical_analyser_memory_requirements(const Config* config) noexcept;

MemoryRequirements parser_memory_requirements(const Config* config) noexcept;

MemoryRequirements source_reader_memory_requirements(const Config* config) noexcept;

MemoryRequirements type_pool_memory_requirements(const Config* config) noexcept;

MemoryRequirements temp_stack_memory_requirements(const Config* config) noexcept;

MemoryRequirements code2_memory_requirements([[maybe_unused]] const Config* config) noexcept;



void comp_heap_init(CoreData* core, MemoryAllocation allocation) noexcept;

void ast_pool_init(CoreData* core, MemoryAllocation allocation) noexcept;

void error_sink_init(CoreData* core, MemoryAllocation allocation) noexcept;

void identifier_pool_init(CoreData* core, MemoryAllocation allocation) noexcept;

void lexical_analyser_init(CoreData* core, MemoryAllocation allocation) noexcept;

void parser_init(CoreData* core, MemoryAllocation allocation) noexcept;

void source_reader_init(CoreData* core, MemoryAllocation allocation) noexcept;

void type_pool_init(CoreData* core, MemoryAllocation allocation) noexcept;

void temp_stack_init(CoreData* core, MemoryAllocation allocation) noexcept;

void code2_init(CoreData* core, MemoryAllocation allocation) noexcept;



void comp_heap_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void ast_pool_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void error_sink_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void identifier_pool_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void lexical_analyser_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void parser_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void source_reader_cleanup([[maybe_unused]] CoreData* core) noexcept;

void type_pool_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void temp_stack_cleanup([[maybe_unused]] CoreData* core) noexcept {}

void code2_cleanup([[maybe_unused]] CoreData* core) noexcept {}


using validate_config_func = bool (*) (const Config* config, PrintSink sink) noexcept;

using memory_requirements_func = MemoryRequirements (*) (const Config* config) noexcept;

using init_func = void (*) (CoreData* core, MemoryAllocation allocation) noexcept;

using cleanup_func = void (*) (CoreData* core) noexcept;

static constexpr validate_config_func VALIDATE_CONFIG_FUNCS[] = {
	&comp_heap_validate_config,
	&temp_stack_validate_config,
	&ast_pool_validate_config,
	&error_sink_validate_config,
	&identifier_pool_validate_config,
	&lexical_analyser_validate_config,
	&type_pool_validate_config,
	&parser_validate_config,
	&source_reader_validate_config,
	&code2_validate_config,
};

static constexpr memory_requirements_func MEMORY_REQUIREMENTS_FUNCS[] = {
	&comp_heap_memory_requirements,
	&temp_stack_memory_requirements,
	&ast_pool_memory_requirements,
	&error_sink_memory_requirements,
	&identifier_pool_memory_requirements,
	&lexical_analyser_memory_requirements,
	&type_pool_memory_requirements,
	&parser_memory_requirements,
	&source_reader_memory_requirements,
	&code2_memory_requirements,
};

static constexpr init_func INIT_FUNCS[] = {
	&comp_heap_init,
	&temp_stack_init,
	&ast_pool_init,
	&error_sink_init,
	&identifier_pool_init,
	&lexical_analyser_init,
	&type_pool_init,
	&parser_init,
	&source_reader_init,
	&code2_init,
};

static constexpr cleanup_func CLEANUP_FUNCS[] = {
	&comp_heap_cleanup,
	&temp_stack_cleanup,
	&ast_pool_cleanup,
	&error_sink_cleanup,
	&identifier_pool_cleanup,
	&lexical_analyser_cleanup,
	&type_pool_cleanup,
	&parser_cleanup,
	&source_reader_cleanup,
	&code2_cleanup,
};

static_assert(array_count(VALIDATE_CONFIG_FUNCS) == CORE_MEMBER_COUNT);

static_assert(array_count(MEMORY_REQUIREMENTS_FUNCS) == CORE_MEMBER_COUNT);

static_assert(array_count(INIT_FUNCS) == CORE_MEMBER_COUNT);

static_assert(array_count(CLEANUP_FUNCS) == CORE_MEMBER_COUNT);



struct MemoryRangeRequirementOffsetComparator
{
	static s32 compare(const MemoryRangeRequirement* a, const MemoryRangeRequirement* b) noexcept
	{
		if (a->max_offset < b->max_offset)
			return -1;
		else if (a->max_offset > b->max_offset)
			return 1;
		else
			return 0;
	}
};

static u32 id_requirements_index_from_ptr(const MemoryRangeRequirement* ptr, const MemoryRequirements* memory_requirements) noexcept
{
	const u32 memory_requirements_index = static_cast<u32>((reinterpret_cast<const byte*>(ptr) - reinterpret_cast<const byte*>(memory_requirements))) / sizeof(MemoryRequirements);

	const u32 id_index = static_cast<u32>(ptr - memory_requirements[memory_requirements_index].ranges);

	return memory_requirements_index * MAX_MEMORY_RANGE_REQUIREMENTS_COUNT + id_index;
}



static CoreMemoryLayout check_config(const Config* config) noexcept
{
	CoreMemoryLayout memory_layout;

	// First, print the config if requested.
	if (config->logging.config_sink.name_and_enabled.attachment())
		print_config(config->logging.config_sink.sink, config);

	// Let every core member validate the given config.

	bool is_valid_config = true;

	const minos::FileHandle config_validation_log_file = minos::standard_file_handle(minos::StdFileName::StdErr);

	for (u64 i = 0; i != CORE_MEMBER_COUNT; ++i)
	{
		if (!VALIDATE_CONFIG_FUNCS[i](config, print_make_sink(config_validation_log_file)))
			is_valid_config = false;
	}

	if (!is_valid_config)
		minos::exit_process(1);

	// Let every core member report its memory requirements.

	MemoryRequirements memory_requirements[CORE_MEMBER_COUNT];

	for (u32 i = 0; i != CORE_MEMBER_COUNT; ++i)
		memory_requirements[i] = MEMORY_REQUIREMENTS_FUNCS[i](config);

	MemoryRangeRequirement* range_requirements_buf[MAX_MEMORY_RANGE_REQUIREMENTS_COUNT * CORE_MEMBER_COUNT];

	u64 range_requirements_count = 0;

	for (MemoryRequirements& req : memory_requirements)
	{
		for (u64 i = 0; i != req.count; ++i)
		{
			ASSERT_OR_IGNORE(range_requirements_count + req.count < array_count(range_requirements_buf));

			range_requirements_buf[range_requirements_count + i] = &req.ranges[i];
		}

		range_requirements_count += req.count;
	}

	const MutRange<MemoryRangeRequirement*> id_requirements{ range_requirements_buf, range_requirements_count };

	inplace_sort<MemoryRangeRequirement*, MemoryRangeRequirementOffsetComparator>(id_requirements);

	const u64 page_mask = minos::page_bytes() - 1;

	u64 total_allocation_size = sizeof(CoreData);

	for (const MemoryRangeRequirement* req : id_requirements)
	{
		total_allocation_size = (total_allocation_size + page_mask) & ~page_mask;

		const u32 reverse_index = id_requirements_index_from_ptr(req, memory_requirements);

		memory_layout.allocations[reverse_index] = RangeAllocation{ total_allocation_size, req->size };

		total_allocation_size += req->size;

		if (total_allocation_size > req->max_offset)
			panic("Could not allocate memory ranges within maximum offset constraints.\n");
	}

	memory_layout.allocation_size = total_allocation_size;

	return memory_layout;
}

static void init_core_data(CoreData* core, const Config* config, const CoreMemoryLayout* memory_layout) noexcept
{
	const u64 page_mask = minos::page_bytes() - 1;

	if (!minos::mem_commit(core, (sizeof(CoreData) + page_mask) & ~page_mask))
		panic("Failed to commit memory for `CoreData` (0x%[|X]).\n", minos::last_error());

	core->config = config;
	core->memory_layout = *memory_layout;


	const bool log_imported_asts = config->logging.imports.asts_sink.name_and_enabled.attachment();
	core->log_imported_asts = log_imported_asts;
	if (log_imported_asts)
		core->imported_asts_sink = config->logging.imports.asts_sink.sink;

	const bool log_imported_code2s = config->logging.imports.code2s_sink.name_and_enabled.attachment();
	core->log_imported_code2s = log_imported_code2s;
	if (log_imported_code2s)
		core->imported_code2s_sink = config->logging.imports.code2s_sink.sink;

	const bool log_imported_types = config->logging.imports.types_sink.name_and_enabled.attachment();
	core->log_imported_types = log_imported_types;
	if (log_imported_types)
		core->imported_types_sink = config->logging.imports.types_sink.sink;



	for (u64 i = 0; i != CORE_MEMBER_COUNT; ++i)
	{
		MemoryAllocation allocation;

		for (u64 j = 0; j != MAX_MEMORY_RANGE_REQUIREMENTS_COUNT; ++j)
		{
			const RangeAllocation range_allocation = memory_layout->allocations[i * MAX_MEMORY_RANGE_REQUIREMENTS_COUNT + j];

			allocation.ranges[j] = MutRange{ reinterpret_cast<byte*>(core) + range_allocation.begin, range_allocation.size };
		}

		INIT_FUNCS[i](core, allocation);
	}
}

static void cleanup_core_data(CoreData* core) noexcept
{
	for (cleanup_func fn : CLEANUP_FUNCS)
		fn(core);
}

CoreData* create_core_data(const Config* config) noexcept
{
	const CoreMemoryLayout memory_layout = check_config(config);

	void* const memory = minos::mem_reserve(memory_layout.allocation_size);

	if (memory == nullptr)
		panic("Failed to reserve memory for `CoreData` (0x%[|X]).\n", minos::last_error());

	CoreData* const core = static_cast<CoreData*>(memory);

	init_core_data(core, config, &memory_layout);

	return core;
}

void release_core_data(CoreData* core) noexcept
{
	cleanup_core_data(core);

	minos::mem_unreserve(core, core->memory_layout.allocation_size);
}

void reset_core_data(CoreData* core) noexcept
{
	const Config* const config = core->config;

	const CoreMemoryLayout memory_layout = core->memory_layout;

	cleanup_core_data(core);

	minos::mem_decommit(core, memory_layout.allocation_size);

	init_core_data(core, config, &memory_layout);
}



static void log_ast(CoreData* core, AstNode* ast) noexcept
{
	if (!core->log_imported_asts)
		return;

	if (diag::print_ast(core->imported_asts_sink, core, ast) < 0)
		panic("Failed to print imported AST.");
}

static void log_code2(CoreData* core, Code2Id block_id) noexcept
{
	if (!core->log_imported_code2s)
		return;

	Code2Block* const block = code2_block_from_id(core, block_id);

	if (diag::print_code2(core->imported_code2s_sink, core, block) < 0)
		panic("Failed to print imported Code2.");
}

static bool file_type_from_ast_definitions(CoreData* core, AstNode* ast, TypeId file_type) noexcept
{
	AstDirectChildIterator it = direct_children_of(ast);

	bool is_ok = true;

	while (has_next(&it))
	{
		AstNode* const node = next(&it);

		Maybe<Code2Id> type_initializer;

		Code2Id value_initializer;

		if (!code2_from_top_level_definition(core, node, &type_initializer, &value_initializer))
		{
			is_ok = false;

			continue;
		}

		if (is_some(type_initializer))
			log_code2(core, get(type_initializer));

		log_code2(core, value_initializer);

		const IdentifierId identifier_id = attachment_of<AstDefinitionData>(node)->identifier_id;

		const bool is_pub = has_flag(node, AstFlag::Definition_IsPub);

		const bool is_mut = has_flag(node, AstFlag::Definition_IsMut);

		FileCompositeMemberInit init{};
		init.name = identifier_id;
		init.type_initializer = type_initializer;
		init.value_initializer = value_initializer;
		init.is_pub = is_pub;
		init.is_mut = is_mut;

		type_add_file_composite_member(core, file_type, init);
	}

	return is_ok;
}

static bool import_file_or_prelude(CoreData* core, Range<char8> path, bool is_prelude, bool is_std, CompileMode mode) noexcept
{
	SourceFileRead read = read_source_file(core, path);

	if (read.source_file->has_error)
		return false;

	if (read.content.begin() == nullptr)
		some(read.source_file->type);

	const Maybe<AstNode*> opt_ast = parse(core, read.content, read.source_file->source_id_base, is_std);

	if (is_none(opt_ast))
	{
		read.source_file->has_error = true;

		return false;
	}

	AstNode* const ast = get(opt_ast);

	const SourceId root_source = source_id_of_ast_node(core, ast);

	const AstFileData* const root_data = attachment_of<AstFileData>(ast);

	const TypeId file_type = type_create_file_composite(core, static_cast<u16>(root_data->member_count), root_source);

	const SourceFileId source_file = id_from_source_file(core, read.source_file);

	read.source_file->ast = id_from_ast_node(core, ast);
	read.source_file->type = file_type;

	if (mode == CompileMode::Parse)
		return true;

	if (is_prelude)
	{
		if (!set_prelude_scope(core, ast, source_file))
		{
			read.source_file->has_error = true;

			return false;
		}
	}
	else
	{
		if (!resolve_names(core, ast, source_file))
		{
			read.source_file->has_error = true;

			return false;
		}
	}

	log_ast(core, ast);

	if (mode == CompileMode::ResolveNames)
		return true;

	if (!file_type_from_ast_definitions(core, ast, file_type))
	{
		read.source_file->has_error = true;

		return false;
	}

	ASSERT_OR_IGNORE(mode == CompileMode::Typecheck || mode == CompileMode::Full);

	return true;
}

static bool run_single_compilation(CoreData* core, bool main_is_std) noexcept
{
	const CompileMode mode = core->config->mode;

	// If we are only parsing, skip the prelude import. It isn't required and
	// kind of skews the measurement.
	if (mode != CompileMode::Parse)
	{
		if (!import_file_or_prelude(core, core->config->std.prelude.filepath, true, true, mode))
			return false;
	}

	if (!import_file_or_prelude(core, core->config->entrypoint.filepath, false, main_is_std, mode))
		return false;

	return true;
}

bool run_compilation(CoreData* core, bool main_is_std) noexcept
{
	const u64 repeats = static_cast<u64>(core->config->benchmark.repeats);
	const u64 timeout_secs = static_cast<u64>(core->config->benchmark.timeout_secs);

	const u64 start_time = minos::timestamp_utc();

	const u64 ticks_per_second = minos::timestamp_ticks_per_second();

	u64 last_report_time = start_time;

	u64 last_report_processed_bytes = 0;

	u64 end_time = 0;

	u64 i = 0;

	u64 processed_bytes = 0;

	do
	{
		if (i != 0)
			reset_core_data(core);

		if (!run_single_compilation(core, main_is_std))
			return false;

		// This is very much *not* clean, but it does the job: The `SourceId`
		// is just continuous byte index into all of the read source files,
		// plus one spacing byte per file.
		processed_bytes += core->reader.curr_source_id_base - core->reader.source_file_count;

		i += 1;

		end_time = minos::timestamp_utc();

		if (repeats != 0 && end_time - last_report_time > 5 * ticks_per_second)
		{
			const u64 elapsed_ms = ((end_time - last_report_time) * 1000) / ticks_per_second;

			const u64 mib_per_s_times_1000 = (((processed_bytes - last_report_processed_bytes) / (1024 * 1024)) * 1000 * 1000) / elapsed_ms;

			const u64 mib_per_s = mib_per_s_times_1000 / 1000;

			const u64 extra_kib_per_s = mib_per_s_times_1000 % 1000;

			print(minos::standard_file_handle(minos::StdFileName::StdErr), "Processing %.%[>03] MiB/s\n", mib_per_s, extra_kib_per_s);

			last_report_processed_bytes = processed_bytes;
			last_report_time = end_time;
		}
	}
	while (i < repeats && (timeout_secs == 0 || end_time - start_time < timeout_secs * ticks_per_second));

	if (repeats != 0)
	{
		const u64 elapsed_ms = ((end_time - start_time) * 1000) / ticks_per_second;

		const u64 mib_per_s_times_1000 = ((processed_bytes / (1024 * 1024)) * 1000 * 1000) / elapsed_ms;

		const u64 mib_per_s = mib_per_s_times_1000 / 1000;

		const u64 extra_kib_per_s = mib_per_s_times_1000 % 1000;

		print(minos::standard_file_handle(minos::StdFileName::StdErr), "Processed % bytes over % iterations in % milliseconds (%.%[>03] MiB/s)\n", processed_bytes, i, elapsed_ms, mib_per_s, extra_kib_per_s);
	}

	return true;
}



void* address_from_core_id(CoreData* core, CoreId id) noexcept
{
	ASSERT_OR_IGNORE((static_cast<u64>(id) << COMP_HEAP_MIN_ALLOCATION_SIZE_LOG2) >= sizeof(CoreData));

	ASSERT_OR_IGNORE((static_cast<u64>(id) << COMP_HEAP_MIN_ALLOCATION_SIZE_LOG2) < core->memory_layout.allocation_size);

	return reinterpret_cast<byte*>(core) + (static_cast<u64>(id) << COMP_HEAP_MIN_ALLOCATION_SIZE_LOG2);
}

CoreId core_id_from_address(CoreData* core, const void* memory) noexcept
{
	ASSERT_OR_IGNORE(memory >= core + 1);

	ASSERT_OR_IGNORE(memory < reinterpret_cast<byte*>(core) + core->memory_layout.allocation_size);

	return static_cast<CoreId>((static_cast<const byte*>(memory) - reinterpret_cast<byte*>(core)) >> COMP_HEAP_MIN_ALLOCATION_SIZE_LOG2);
}



const char8* tag_name(Builtin builtin) noexcept
{
	static constexpr const char8* BUILTIN_NAMES[] = {
		"INVALID",
		"Integer",
		"Float",
		"Type",
		"Definition",
		"TypeInfo",
		"Typeof",
		"Returntypeof",
		"Sizeof",
		"Alignof",
		"Strideof",
		"ArrayCountof",
		"Offsetof",
		"Nameof",
		"Import",
		"CreateTypeBuilder",
		"AddTypeMember",
		"CompleteType",
		"SourceId",
		"CallerSourceId",
		"DefinitionTypeof",
		"ForeignFunctionImport",
		"ForeignFunctionCall",
		"CompilerHostOs",
		"CompilerHostArch",
		"CompilerMajorVersion",
		"CompilerMinorVersion",
		"CompDefinesType",
		"CompDefines",
	};

	u8 ordinal = static_cast<u8>(builtin);

	if (ordinal >= array_count(BUILTIN_NAMES))
		ordinal = 0;

	return BUILTIN_NAMES[ordinal];
}
