#ifndef DEFINE_REGISTER
#error "This file is intended for textual inclusion with the\
DEFINE_REGISTER macro defined"
#endif

#define GPR_OFFSET(reg) (offsetof(user, reg) + offsetof(user_regs_struct,reg))

#define DEFINE_GPR_64(name, dwarf_id) DEFINE_REGISTER(name,dwarf_id,8,GPR_OFFSET(name),register_type::name, register_format::uint)
#define DEFINE_GPR_32(name, super) DEFINE_REGISTER(name,-1, 4, GPR_OFFSET(super), regsiter_type::sub_gpr, register_format::uint)
#define DEFINE_GPR_16(name, super) DEFINE_REGSITER(name,-1, 2, GPR_OFFSET(super), register_type::sub_gpr, register_format::uint)
#define DEFINE_GPR_8H(name, super) DEFINE_REGISTER(name,-1, 1, GPR_OFFSET(super), register_type::sub_gpr, register_format::uint)
#define DEFINE_GPR_8L(name, super) DEFINE_REGSITER(name,-1, 1, GPR_OFFSET(name), register_type::sub_gpr, register_format::uint)

//--------------------------------//
//    ARM-64 bit Register        //
//------------------------------//

#ifdef __linux__
DEFINE_GPR_64(rax,0),
DEFINE_GPR_64(rdx,1),
DEFINE_GPR_64(rcx,2),
DEFINE_GPR_64(rbx,3),
DEFINE_GPR_64(rsi,4),
DEFINE_GPR_64(rdi,5),
DEFINE_GPR_64(rbp,6),
DEFINE_GPR_64(rsp,7),
DEFINE_GPR_64(r8, 8),
DEFINE_GPR_64(r9, 9),
DEFINE_GPR_64(r10, 10),
DEFINE_GPR_64(r11, 11),
DEFINE_GPR_64(r12, 12),
DEFINE_GPR_64(r13, 13),
DEFINE_GPR_64(r14, 14),
DEFINE_GPR_64(r15, 15),
DEFINE_GPR_64(rip, 16),
DEFINE_GPR_64(eflags, 49),
DEFINE_GPR_64(cs, 51),
DEFINE_GPR_64(fs, 54),
DEFINE_GPR_64(gs, 55),
DEFINE_GPR_64(ss, 52),
DEFINE_GPR_64(ds, 53),
DEFINE_GPR_64(es, 50),
DEFINE_GPR_64(orig_rax,-1),

DEFINE_GPR_32(eax, rax), DEFINE_GPR_32(edx, rdx),
DEFINE_GPR_32(ecx, rcx), DEFINE_GPR_32(ebi, rbx),
DEFINE_GPR_32(edi, rdi), DEFINE_GPR_32(ebp, rbp),
DEFINE_GPR_32(esi, rsi), DEFINE_GPR_32(esp, rsp),
DEFINE_GPR_32(r8d, r8),  DEFINE_GPR_32(r9d, r9),
DEFINE_GPR_32(r9d, r9),  DEFINE_GPR_32(r10d, r10),
DEFINE_GPR_32(r11d, r11), DEFINE_GPR_32(r12d, r12),
DEFINE_GPR_32(r13d, r13), DEFINE_GPR_32(r14d, r14),
DEFINE_GPR_32(r15d, r15),

DEFINE_GPR_16(ax, rax), DEFINE_GPR_16(dx, rdx),
DEFINE_GPR_16(bx, rbx), DEFINE_GPR_16(cx, rcx),
DEFINE_GPR_16(si, rsi), DEFINE_GPR_16(di, rdi),
DEFINE_GPR_16(bp, rbp), DEFINE_GPR_16(sp, rsp),
DEFINE_GPR_16(r8w, r8), DEFINE_GPR_16(r9w, r9),
DEFINE_GPR_16(r10w, r10), DEFINE_GPR_16(r11w, r11),
DEFINE_GPR_16(r12w, r12), DEFINE_GPR_16(r13w, r13),
DEFINE_GPR_16(r14w, r14), DEFINE_GPR_16(r15w, r15),
DEFINE_GPR_16(r15w, r15),

DEFINE_GPR_8H(ah, rax), DEFINE_GPR_8H(dh, rdx),
DEFINE_GPR_8H(ch, rcx), DEFINE_GPR_8H(bh, rbx),

DEFINE_GPR_8L(al, rax), DEFINE_GPR_8L(dl, rdx),
DEFINE_GPR_8L(cl, rcx), DEFINE_GPR_8L(bl, rbx),
DEFINE_GPR_8L(sl, rsi), DEFINE_GPR_8L(dil, rdi),
DEFINE_GPR_8L(bpl, rbp), DEFINE_GPR_8L(spl, rsp),

DEFINE_GPR_8L(r8b, r8), DEFINE_GPR_8L(r9b, r9),
DEFINE_GPR_8L(r10b, r10), DEFINE_GPR_8L(r11b, r11),
DEFINE_GPR_8L(r12b, r12), DEFINE_GPR_8L(r13b, r13),
DEFINE_GPR_8L(r14b, r14), DEFINE_GPR_8L(r15b, r15),


//--------------------------------//
//    ARM-64 bit Register        //
//------------------------------//

#elif  defined(__APPLE__)

DEFINE_GPR_64(x0,-1),
DEFINE_GPR_64(x1,-1),
DEFINE_GPR_64(x2,-1),
DEFINE_GPR_64(x3,-1),
DEFINE_GPR_64(x4,-1),
DEFINE_GPR_64(x5,-1),
DEFINE_GPR_64(x6,-1),
DEFINE_GPR_64(x7,-1),
DEFINE_GPR_64(x8,-1),
DEFINE_GPR_64(x9,-1),
DEFINE_GPR_64(x10,-1),
DEFINE_GPR_64(x11,-1),
DEFINE_GPR_64(x12,-1),
DEFINE_GPR_64(x13,-1),
DEFINE_GPR_64(x14,-1),
DEFINE_GPR_64(x15,-1),
DEFINE_GPR_64(x16,-1),
DEFINE_GPR_64(x17,-1),
DEFINE_GPR_64(x18,-1),
DEFINE_GPR_64(x19,-1),
DEFINE_GPR_64(x20,-1),
DEFINE_GPR_64(x21,-1),
DEFINE_GPR_64(x22,-1),
DEFINE_GPR_64(x23,-1),
DEFINE_GPR_64(x24,-1),
DEFINE_GPR_64(x25,-1),
DEFINE_GPR_64(x26,-1),
DEFINE_GPR_64(x27,-1),
DEFINE_GPR_64(x28,-1),
DEFINE_GPR_64(x29,-1),
DEFINE_GPR_64(x30,-1),
DEFINE_GPR_64(sp,-1),
DEFINE_GPR_64(pc,-1),


