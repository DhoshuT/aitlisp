#ifndef H_PROC
#define H_PROC

#include "lisp_mt.h"

#define PROCTYPE(proc) L_obj (proc)(L_obj, L_obj, L_obj)
#define PROC(name,x,y,z) L_obj name (L_obj (x), L_obj (y), L_obj (z))

#define MAX_REG_PROCS 100

int N_Regprocs; //(組み込み)基本関数の数

PROCTYPE( *RegisteredProcs[MAX_REG_PROCS +1] );

GLOBAL L_obj proc_call(L_obj atm, L_obj x, L_obj y, L_obj z);
GLOBAL void register_atoms();
GLOBAL void register_aliases();

GLOBAL PROCTYPE(p_car);
GLOBAL PROCTYPE(p_cdr);
GLOBAL PROCTYPE(p_cons);
GLOBAL PROCTYPE(p_atom);
GLOBAL PROCTYPE(p_eq);
GLOBAL PROCTYPE(p_neq);
GLOBAL PROCTYPE(p_display);
GLOBAL PROCTYPE(p_debug);
GLOBAL PROCTYPE(p_append);
GLOBAL PROCTYPE(p_length);
GLOBAL PROCTYPE(p_lt);
GLOBAL PROCTYPE(p_gt);
GLOBAL PROCTYPE(p_le);
GLOBAL PROCTYPE(p_ge);
GLOBAL PROCTYPE(p_add);
GLOBAL PROCTYPE(p_times);
GLOBAL PROCTYPE(p_power);
GLOBAL PROCTYPE(p_sub);
GLOBAL PROCTYPE(p_div);
GLOBAL PROCTYPE(p_remainder);
GLOBAL PROCTYPE(p_base2_to_10);
GLOBAL PROCTYPE(p_base10_to_2);
GLOBAL PROCTYPE(p_size);
GLOBAL PROCTYPE(p_read_bit);
GLOBAL PROCTYPE(p_bits);
GLOBAL PROCTYPE(p_read_exp);
GLOBAL PROCTYPE(p_quit);
GLOBAL PROCTYPE(p_load);
GLOBAL PROCTYPE(p_show_strg);
GLOBAL PROCTYPE(p_show_tree);
GLOBAL PROCTYPE(p_show_atom);
GLOBAL PROCTYPE(p_show_all_atoms);
GLOBAL PROCTYPE(p_help);

typedef struct _reg_atom_properties{
    int tflag; //0:定数, 1:基本関数, 2:特殊構文, 3:糖構文
    L_obj *atomp;
    char *name;
    short args;
    PROCTYPE(*procp);
}reg_atoms;

typedef struct _alias{
    char *name;
    L_obj *atomp;
}alias;

#endif