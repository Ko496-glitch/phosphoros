#ifndef DEFINE_REGISTER
#error "This file is intended for textual inclusion with the\
DEFINE_REGISTER macro defined"
#endif


/* --------------------------------------------------------x86 Register-----------------------------------------------------------------------  - */
//--------------------------------//
//    x86-64 bit macros          //
//------------------------------//
#ifdef __linux__
#define GPR_OFFSET(reg) (offsetof(user, reg) + offsetof(user_regs_struct,reg))
#define DEFINE_GPR_64(name, dwarf_id) DEFINE_REGISTER(name,dwarf_id,8,GPR_OFFSET(name),register_type::name, register_format::uint)
#define DEFINE_GPR_32(name, super) DEFINE_REGISTER(name,-1, 4, GPR_OFFSET(super), regsiter_type::sub_gpr, register_format::uint)
#define DEFINE_GPR_16(name, super) DEFINE_REGSITER(name,-1, 2, GPR_OFFSET(super), register_type::sub_gpr, register_format::uint)
#define DEFINE_GPR_8H(name, super) DEFINE_REGISTER(name,-1, 1, GPR_OFFSET(super), register_type::sub_gpr, register_format::uint)
#define DEFINE_GPR_8L(name, super) DEFINE_REGSITER(name,-1, 1, GPR_OFFSET(name), register_type::sub_gpr, register_format::uint)
#define FPR_OFFSET(reg) (offsetof(user, i387) + offsetof(user_fpregs_struct, reg))
#define FPR_OFFSET(reg) (sizeof(user_fpregs_struct::reg)
#define DEFINE_FPR(name,dwarf_id, user_name) DEFINE_REGISTER(name, dwarf_id, FPR_SIZE(user_name),FPR_OFFSET(user_name), register_type::fpr, register_format::uint)
#define DEFINE_FP_ST(number) DEFINE_REGISTER(st ##number, (33 + number), 16, (FPR_OFFSET(st_space) + number *16), regsiter_type::fpr, register_format::long_double)
#define DEFINE_FP_MM(number) DEFINE_REGISTER(mm ##number, (41 + number), 8, (FPR_OFFSET(st_space) + number * 16), register_type::fpr, register_format::vector)
#define DEFINE_FP_XMM(number) DEFINE_REGISTER(xmm ##number, (17 + number), 16, (FPR_OFFSET(st_space) + number *16, register_type::fpr,  register_format::vector)
#define DR_OFFSET(number) (offsetof(user, u_debugging) + number * 8)
#define DEFINE_DR(number) DEFINE_REGISTER(dr ## number, -1, 8 , DR_OFFSET(number), register_type::dr, register_format::uint)

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

DEFINE_FPR(fcw, 65, , cwd),
DEFINE_FPR(fsw, 66, swd),
DEFINE_FPR(ftw, -1, ftd),
DEFINE_FPR(fop, -1, fop),
DEFINE_FPR(frip, -1, rip),
DEFINE_FPR(frdp, -1, rdp),
DEFINE_FPR(mxcr, 64, mxcsr),
DEFINE_FPR(mxcsrmask, -1, mxcr_mask),


DEFINE_FPR_ST(0), DEFINE_FPR_ST(1), DEFINE_FPR_ST(2), DEFINE_FPR_ST(3), DEFINE_FPP_ST(4),
DEFINE_FPR_ST(5), DEFINE_FPR_ST(6), DEFINE_FPR_ST(7),

DEFINE_FPR_MM(0), DEFINE_FPR_MM(1), DEFINE_FPR_MM(2), DEFINE_FPR_MM(3), DEFINE_FPP_MM(4),
DEFINE_FPR_MM(5), DEFINE_FPR_MM(6), DEFINE_FPR_MM(7),


DEFINE_FPR_XMM(0), DEFINE_FPR_XMM(1), DEFINE_FPR_XMM(2), DEFINE_FPR_XMM(3), DEFINE_FPP_XMM(4),
DEFINE_FPR_XMM(5), DEFINE_FPR_XMM(6), DEFINE_FPR_XMM(7),DEFINE_FPR_XMM(8), DEFINE_FPR_XMM(9), 
DEFINE_FPR_XMM(10), DEFINE_FPR_XMM(11), DEFINE_FPP_XMM(12),DEFINE_FPR_XMM(13), DEFINE_FPR_XMM(14), DEFINE_FPR_XMM(157),

DEFINE_DR(0), DEFINE_DR(1), DEFINE_DR(2), DEFINE_DR(3), DEFINE_DR(4),
DEFINE_DR(5), DEFINE_DR(6), DEFINE(7),


/* --------------------------------------------------------AArch 64 Register-----------------------------------------------------------------------  - */
//--------------------------------//
//    AArch-64 bit macros          //
//------------------------------//
#elif defined(__APPLE__)

#define GPR_OFFSET(regs_idx) (offsetof(user_pt_regs, regs[regs_idx]))
#define DEFINE_GPR_64(name, dwarf_id) DEFINE_REGISTER(name,dwarf_id,8,GPR_OFFSET(name), register_type::name, register_format::uint64)
#define DEFINE_GPR_32(name, super) DEFINE_RESGITER(name, -1, 8,  GPR_OFFSET(super), register_type::sub_gpr, register_format::uint32)


#define FPR_OFFSET(regs_idx) (offsetof(user_fpsimd_state,vregs[regs_idx])
#define DEFINE_FPR(name, dwarf_id) DEFINE_REGISTER(name,dward_id,16, FPR_OFFSET(name), register_format::fpr, register_type::_uint128_t)


DEFINE_GPR_64(x0,0),
DEFINE_GPR_64(x1,1),
DEFINE_GPR_64(x2,2),
DEFINE_GPR_64(x3,3),
DEFINE_GPR_64(x4,4),
DEFINE_GPR_64(x5,5),
DEFINE_GPR_64(x6,6),
DEFINE_GPR_64(x7,7),
DEFINE_GPR_64(x8,8),
DEFINE_GPR_64(x9,9),
DEFINE_GPR_64(x10,10),
DEFINE_GPR_64(x11,11),
DEFINE_GPR_64(x12,12),
DEFINE_GPR_64(x13,13),
DEFINE_GPR_64(x14,14),
DEFINE_GPR_64(x15,15),
DEFINE_GPR_64(x16,16),
DEFINE_GPR_64(x17,17),
DEFINE_GPR_64(x18,18),
DEFINE_GPR_64(x19,19),
DEFINE_GPR_64(x20,20),
DEFINE_GPR_64(x21,21),
DEFINE_GPR_64(x22,22),
DEFINE_GPR_64(x23,23),
DEFINE_GPR_64(x24,24),
DEFINE_GPR_64(x25,25),
DEFINE_GPR_64(x26,26),
DEFINE_GPR_64(x27,27),
DEFINE_GPR_64(x28,28),
DEFINE_GPR_64(x29,29),
DEFINE_GPR_64(x30,30),
DEFINE_GPR_64(sp,31),
DEFINE_GPR_64(pc,32),
DEFINE_GPR_64(orig_rax,-1),

DEFINE_GPR_32(w0, -1),
DEFINE_GPR_32(w1, -1),
DEFINE_GPR_32(w2, -1),
DEFINE_GPR_32(w3, -1),
DEFINE_GPR_32(w4, -1),
DEFINE_GPR_32(w5, -1),
DEFINE_GPR_32(w6, -1),
DEFINE_GPR_32(w7, -1),
DEFINE_GPR_32(w8, -1),
DEFINE_GPR_32(w9, -1),
DEFINE_GPR_32(w10, -1),
DEFINE_GPR_32(w11, -1),
DEFINE_GPR_32(w12, -1),
DEFINE_GPR_32(w13, -1),
DEFINE_GPR_32(w14, -1),
DEFINE_GPR_32(w15, -1),
DEFINE_GPR_32(w16, -1),
DEFINE_GPR_32(w17, -1),
DEFINE_GPR_32(w18, -1),
DEFINE_GPR_32(w19, -1),
DEFINE_GPR_32(w20, -1),
DEFINE_GPR_32(w21, -1),
DEFINE_GPR_32(w22, -1),
DEFINE_GPR_32(w23, -1),
DEFINE_GPR_32(w24, -1),
DEFINE_GPR_32(w25, -1),
DEFINE_GPR_32(w26, -1),
DEFINE_GPR_32(w27, -1),
DEFINE_GPR_32(w28, -1),
DEFINE_GPR_32(w29, -1),
DEFINE_GPR_32(w30, -1),


DEFINE_FPR_128(v0, 64),
DEFINE_FPR_128(v1, 65),
DEFINE_FPR_128(v2, 66),
DEFINE_FPR_128(v3, 67),
DEFINE_FPR_128(v4, 68),
DEFINE_FPR_128(v5, 69),
DEFINE_FPR_128(v6, 70),
DEFINE_FPR_128(v7, 71),
DEFINE_FPR_128(v8, 72),
DEFINE_FPR_128(v9, 73),
DEFINE_FPR_128(v10, 74),
DEFINE_FPR_128(v11, 75),
DEFINE_FPR_128(v12, 76),
DEFINE_FPR_128(v13, 77),
DEFINE_FPR_128(v14, 78),
DEFINE_FPR_128(v15, 79),
DEFINE_FPR_128(v16, 80),
DEFINE_FPR_128(v17, 81),
DEFINE_FPR_128(v17, 82),
DEFINE_FPR_128(v18, 83),
DEFINE_FPR_128(v19, 84),
DEFINE_FPR_128(v20, 85),
DEFINE_FPR_128(v21, 86),
DEFINE_FPR_128(v22, 87),
DEFINE_FPR_128(v23, 88),
DEFINE_FPR_128(v24, 89),
DEFINE_FPR_128(v25, 90),
DEFINE_FPR_128(v26, 91),
DEFINE_FPR_128(v27, 92),
DEFINE_FPR_128(v28, 93),
DEFINE_FPR_128(v29, 94),
DEFINE_FPR_128(v30, 95),
