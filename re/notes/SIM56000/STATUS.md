# SIM56000 status
- step 3 (naming agents): launched, groups A-H (see re/names/SIM56000/*.names.txt, re/notes/SIM56000/<group>.md)
- step 4/5: not started
- step 1 (hidden functions) done: 2260 functions in re/out/SIM56000 (scripts/CreateHidden.java, hidden_SIM56000.txt, namehidden.py); step 2 done: names merged (override.txt), splitsim2.py/filemap.txt; step 3 in progress
- step 3: gentab_sim.py + simdata.py generate src/sim56000/simd_*.c/simdata.h (auto layout of ALL initialized data); header/TRANSLATE pending
- data generators verified (47k values); simdata.h/simd_*.c compile gcc + m68k -mshort; remaining: sim56000.h, TRANSLATE.md
- DONE (this pass): hidden functions created in Ghidra (2260 fn), names merged, corrected filemap (splitsim2.py), src/sim56000/{sim56000.h,simdata.h,simd_*.c,simbss.c,simproto.h} generated+verified, TRANSLATE.md (10 work packages)
- regenerate: python re/scripts/gentab_sim.py ; python re/scripts/genproto_sim.py ; verify: gentab_sim.py --verify then build re/out/SIM56000/simverify*.c with simd_*.c and compare with simverify.exp (mod CR)

## Translation started (2026-10-02)

P1 foundation: `src/sim56000/avltree.c` implements four routines:
`avl_set_node`, `avl_rebalance`, `avl_walk`, `avl_walk_node`.
The remaining AVL routines (allocation, insert/delete, find, copy and iterator)
are pending; no complete simulator executable exists yet.

Original x86 disassembly confirms that `avl_set_node` and `avl_rebalance`
return node pointers. Naming sources and generated `simproto.h` now reflect
those returns and use real callback pointer types for traversal. No shared
structure members were changed.

Validation: `make sim56000-tests` checks node heights, root preservation,
single/double rotations, middle-subtree preservation, all six traversal orders,
all bracket modes, and null/empty trees. These are structural tests, not
original-console transcript comparisons. The original EXEs were restored from
the supplied archive into ignored `re/bin/` for disassembly. The m68k compiler
is unavailable on this host, so its 16-bit-int build remains unverified.

## AVL translation extended (2026-10-02)

All 14 functions in `avltree.c` are translated, including allocator selection,
insertion/deletion, exact and nearest lookup, shallow copying, in-place sorting
with node reuse, and bounded iteration. This supersedes the four-routine status
above. Integration still requires the profiler allocator, pool allocator and
actual comparator implementations; tests provide explicit mocks for these.

Machine-code checks resolved the insertion flag: nonzero allows duplicates,
rather than replacing a matching payload. Comparators compare the key to the
stored item (0 lower, 1 equal, 2 higher). Iteration accepts a start key as its
second argument when initialized and an inclusive end key as its third.
`repeat == 1` in deletion loops unconditionally in the original; all recovered
callers pass zero. That quirk is preserved and excluded from terminating tests.

Shared definitions now include the profiler's embedded six-word `sim_pool`,
its `heap_mode` member, and declarations for profiler/AVL globals. Iterator and
pool allocation pointer prototypes were corrected in the naming sources.
Generated comparator records now use `simcmp`, with matching typed declarations
and verification stubs; no table values were changed.

Validation: C89 build and `make sim56000-tests` pass, as do address/undefined
behavior sanitizers, prototype regeneration and the ANSI source checker.
Tests cover 257-key insertion/deletion permutations, duplicate payloads, nearest
neighbors, all comparator slots, bounded and interleaved iterators, both allocator
branches, copied/reordered trees, node reuse and free modes. Full simulator
transcripts and a 16-bit-int m68k build remain pending.

Data verification also exposed a pre-existing generated `extern void main()`
declaration rejected by the host compiler. The generator now declares an
integer-returning entry point and casts its unused table reference explicitly.

Regenerated data verification passes: all 47,437 scalar/string entries match
the original image (47,470 output lines because some strings contain newlines).

## Allocation and pool dependencies translated (2026-10-02)

Fifteen more routines are implemented (29 simulator routines total):
- `radix.c`: `dsp_alloc`, `dsp_free`, `dsp_realloc`.
- `console.c`: `pool_init`, `pool_new_block`, `pool_alloc`, `pool_strdup`,
  `chain_free`, `avl_cmp_h43de70`.
- `profdata.c`: `prof_list_count`, `prof_malloc`, `prof_swap32`, `prof_cmp_ulong`.
- `miscx.c`: original no-op `dsp_free_ext` hook.

The pool's shared header now uses typed block pointers and a `pool_block`
structure. The original cursor is represented by a byte count, avoiding raw
structure offsets. Pointer prototypes are corrected in the naming sources.
`profdata.c` owns `prof_ctx` and the portable `jmp_buf prof_jmpbuf`.

`make sim56000-tests` now includes real allocator/pool/AVL integration, with
only libc failure injection, disk spilling and output mocked. The previous AVL
unit tests still use explicit allocator/comparator mocks for isolated coverage.
Pooled objects have arena lifetime and are freed through `chain_free`; individual
AVL frees are exercised on heap allocations. The pool deliberately retains the
original configured-capacity check after oversized blocks and leaves the freed
head unchanged, matching the recovered code.

Coverage includes zero-fill and uninitialized allocation, spill retries,
allocation/reallocation exhaustion, preservation of a failed realloc's input,
error output in the selected device context and restoration of current pointers,
profiler flag/longjmp behavior, the inactive GUI allocation path, pool growth,
string storage, eight-byte allocation rounding, oversized blocks, arena cleanup,
and AVL creation/copy/reorder/delete/iteration with reconstructed allocators.
The two recovered comparators preserve 32-bit signed/unsigned ordering on wider
hosts; the remaining eleven comparator functions are pending.

`make sim56000-modules` compiles the production modules without failure injection.
The remaining memory-disk spill and transcript output implementations, other P1
modules, full simulator executable and m68k validation are still pending.

Validation for this allocation pass: `make sim56000-tests`, production C89
module compilation, address/undefined-behavior sanitizers, prototype
regeneration check, ANSI source checks and whitespace checks all pass. The
existing generic `simfn` declaration still produces host compiler warnings.
