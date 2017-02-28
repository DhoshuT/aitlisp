#include "lisp_mt.h"
#include "proc.h"

reg_atoms reg_atoms_tbl[] = {
    { 0, &wrd_nil,   "nil",   0, NULL },
    { 0, &wrd_true,  "true",  0, NULL },
    { 0, &wrd_false, "false", 0, NULL },
    { 0, &wrd_no_time_limit, "no-time-limit", 0, NULL },
    { 0, &wrd_out_of_time,   "out-of-time",   0, NULL },
    { 0, &wrd_out_of_data,   "out-of-data",   0, NULL },
    { 0, &wrd_success,   "success",   0, NULL },
    { 0, &wrd_failure,   "failure",   0, NULL },
    { 0, &left_bracket, "[",   0, NULL },
    { 0, &right_bracket,"]",   0, NULL },
    { 0, &left_paren,   "(",   0, NULL },
    { 0, &right_paren,  ")",   0, NULL },
    { 0, &double_quote, "\"",  0, NULL },
    { 0, &wrd_find_EOF, "find_EOF", 0, NULL },
    { 0, &wrd_division_with_zero, "division-with-zero", 0, NULL },
    { 2, &wrd_define, "define", 3, NULL },
    { 2, &wrd_lambda, "lambda", 3, NULL },
    { 2, &wrd_quote,  "'",      2, NULL },
    { 2, &wrd_if,     "if",     4, NULL },
    { 2, &wrd_eval,   "eval",   2, NULL },
    { 2, &wrd_try,    "try",    4, NULL },
    { 3, &wrd_let,    "let",    4, NULL },
    { 3, &wrd_not, "not", 2, NULL },
    { 3, &wrd_and, "and", 3, NULL },
    { 3, &wrd_or,  "or",  3, NULL },
    { 3, &wrd_run_utm_on, "run-utm-on", 2, NULL },
    { 3, &wrd_caar,   "caar",  2, NULL },
    { 3, &wrd_cadr,   "cadr",  2, NULL },
    { 3, &wrd_caddr,  "caddr", 2, NULL },
    { 3, &wrd_caddr,  "caddr", 2, NULL },
    { 1, &wrd_car,    "car",   2, p_car  },
    { 1, &wrd_cdr,    "cdr",   2, p_cdr  },
    { 1, &wrd_cons,   "cons",  3, p_cons },
    { 1, &wrd_atom,   "atom?", 2, p_atom },
    { 1, &wrd_eq,  "=",  3, p_eq  },
    { 1, &wrd_neq, "!=", 3, p_neq },
    { 1, &wrd_display, "display", 2, p_display },
    { 1, &wrd_debug,   "debug",   2, p_debug   },
    { 1, &wrd_append,  "append",  3, p_append  },
    { 1, &wrd_length,  "length",  2, p_length  },
    { 1, &wrd_lt,    "<",  3, p_lt    },
    { 1, &wrd_gt,    ">",  3, p_gt    },
    { 1, &wrd_le,    "<=", 3, p_le    },
    { 1, &wrd_ge,    ">=", 3, p_ge    },
    { 1, &wrd_add,   "+",  3, p_add   },
    { 1, &wrd_times, "*",  3, p_times },
    { 1, &wrd_power, "^",  3, p_power },
    { 1, &wrd_sub,   "-",  3, p_sub   },
    { 1, &wrd_div,   "/",  3, p_div   },
    { 1, &wrd_remainder,   "remainder",   3, p_remainder   },
    { 1, &wrd_base2_to_10, "base2-to-10", 2, p_base2_to_10 },
    { 1, &wrd_base10_to_2, "base10-to-2", 2, p_base10_to_2 },
    { 1, &wrd_size,     "size",     2, p_size     },
    { 1, &wrd_read_bit, "read-bit", 1, p_read_bit },
    { 1, &wrd_bits,     "bits",     2, p_bits     },
    { 1, &wrd_read_exp, "read-exp", 1, p_read_exp },
    { 1, &wrd_quit,     "quit",     1, p_quit },
    { 1, &wrd_load,     "load",     2, p_load },
    { 1, &wrd_show_strg, "show-strg", 1, p_show_strg },
    { 1, &wrd_show_tree, "show-tree", 2, p_show_tree },
    { 1, &wrd_show_atom, "show-atom", 2, p_show_atom },
    { 1, &wrd_show_all_atoms, "show-all-atoms", 1, p_show_all_atoms },
    { 1, &wrd_help, "help", 1, p_help },
    { 0, NULL, "", 0, NULL } //dummy: end of table
};

#define end_of_rT(i) ( reg_atoms_tbl[i].atomp == NULL )

L_obj proc_call(L_obj atom, L_obj x, L_obj y, L_obj z){
    PROCTYPE(*proc) = RegisteredProcs[Pf_numb[atom]];
    // printf("%d/%d\n",Pf_numb[atom],N_Regprocs);
    return proc(x,y,z);
}

void register_atoms(){
    int i, np=0;
    int fg;
    L_obj *ap;

    fg = reg_atoms_tbl[0].tflag;
    ap = reg_atoms_tbl[0].atomp;
    for(i=0; (!(end_of_rT(i)) && i < MAX_REG_PROCS);){
        switch(fg){ //Pf_numb = np > 0 とする
        case 1:
            np++;
            *ap = mk_atom(np,reg_atoms_tbl[i].name,
                             reg_atoms_tbl[i].args);
            RegisteredProcs[np] = reg_atoms_tbl[i].procp;
            break;
        default:    //Pf_numb = 0
            *ap = mk_atom(0,reg_atoms_tbl[i].name,
                            reg_atoms_tbl[i].args);
        }
        i++;
        fg = reg_atoms_tbl[i].tflag;
        ap = reg_atoms_tbl[i].atomp;
    }
    N_Regprocs = np;
}

alias alias_tbl[] = {
    { "def", &wrd_define },
    { "lmd", &wrd_lambda },
    { "apd", &wrd_append },
    { "a?",  &wrd_atom },
    { "!",   &wrd_not },
    { "&",   &wrd_and },
    { "|",   &wrd_or },
    { "rem", &wrd_remainder },
    { "len", &wrd_length },
    { "r-e", &wrd_read_exp },
    { "r-b", &wrd_read_bit },
    { "dsp", &wrd_display },
    { "ruo", &wrd_run_utm_on  },
    { "d2b", &wrd_base10_to_2 },
    { "b2d", &wrd_base2_to_10 },
    { "qt",  &wrd_quit },
    { "ld",  &wrd_load },
    { "ss",  &wrd_show_strg },
    { "st",  &wrd_show_tree },
    { "sa",  &wrd_show_atom },
    { "saa", &wrd_show_all_atoms },
    { "#oot",&wrd_out_of_time  },
    { "#ood",&wrd_out_of_data  },
    { "#ntl",&wrd_no_time_limit },
    { "#f",  &wrd_false },
    { "#t",  &wrd_true },
    { "\0",  NULL } //dummy: end of table
};

#define end_of_aT(i) ( *(alias_tbl[i].name) == '\0' )

void register_aliases(){
    int i;
    char *nm;
    nm = alias_tbl[0].name;
    for(i=0; !(end_of_aT(i)); ){
        mk_alias(nm,*alias_tbl[i].atomp);
        i++;
        nm = alias_tbl[i].name;
    }
}

L_obj show_keywords(){
    int i,j,ca=0;
    L_obj a,aa;
    char *name, *aname;
    for(i=0; !(end_of_rT(i)); i++){
        a = *(reg_atoms_tbl[i].atomp);
        name = reg_atoms_tbl[i].name;
        printf("%3d: %s",i+1,name);
        for(j=0; !(end_of_aT(j)); j++){
            aa = *(alias_tbl[j].atomp);
            aname = alias_tbl[j].name;
            if(a == aa){
                printf(" --> %s",aname);
                ca++;
                break;
            }
        }
        putchar('\n');
    }
    return cons(mk_numb_from_long((long) i),
                cons(wrd_add,
                     cons(mk_numb_from_long((long) ca),NIL)));
}

PROC(p_car, x, y, z){
    return Car[x];
}
PROC(p_cdr, x, y, z){
    return Cdr[x];
}
PROC(p_cons, x, y, z){
    return cons(x,y);
}
PROC(p_atom, x, y, z){
    return (is_atom(x) ? wrd_true : wrd_false);
}
PROC(p_eq, x, y, z){
    return (eq(x,y) ? wrd_true  : wrd_false);
}
PROC(p_neq, x, y, z){
    return (eq(x,y) ? wrd_false : wrd_true);
}
PROC(p_display, x, y, z){
    L_obj stub, old_end, new_end;
    if (Car[display_enabled]){
        return out("display",x);
    }
    else{
        stub = Car[captured_displays];
        old_end = Car[stub];
        new_end = cons(x,NIL);
        Cdr[old_end] = new_end;
        Car[stub] = new_end;
        return x;
    }
    return NIL; //dummyreturn
}
PROC(p_debug, x, y, z){
    return out("debug",x);
}
PROC(p_append, x, y, z){
    return append((is_atom(x)? NIL:x),(is_atom(y)? NIL:y));
}
PROC(p_length, x, y, z){
    return mk_numb(length(x));
}
PROC(p_lt, x, y, z){
    return (compare(nmb(x),nmb(y)) == '<' ? wrd_true : wrd_false);
}
PROC(p_gt, x, y, z){
    return (compare(nmb(x),nmb(y)) == '>' ? wrd_true : wrd_false);
}
PROC(p_le, x, y, z){
    return (compare(nmb(x),nmb(y)) != '>' ? wrd_true : wrd_false);
}
PROC(p_ge, x, y, z){
    return (compare(nmb(x),nmb(y)) != '<' ? wrd_true : wrd_false);
}
PROC(p_add, x, y, z){
    return mk_numb(addition(nmb(x),nmb(y),0));
}
PROC(p_times, x, y, z){
    return mk_numb(multiplication(nmb(x),nmb(y)));
}
PROC(p_power, x, y, z){
    return mk_numb(power(nmb(x),nmb(y)));
}
PROC(p_sub, x, y, z){
    return mk_numb(subtraction(nmb(x),nmb(y)));
}
PROC(p_div, x, y, z){
    if(is_zero(y)) 
        return - wrd_division_with_zero; /* error */
    else 
        return mk_numb(quot(division(nmb(x),nmb(y))));
}
PROC(p_remainder, x, y, z){
     if(is_zero(y))
        return - wrd_division_with_zero; /* error */
     else
        return mk_numb(rem(division(nmb(x),nmb(y))));
}
PROC(p_base2_to_10, x, y, z){
    return mk_numb(base2_to_10(x));
}
PROC(p_base10_to_2, x, y, z){
    return base10_to_2(nmb(x));
}
PROC(p_size, x, y, z){ //size of print representation of x
    return mk_numb(size(x));
}
PROC(p_read_exp, x, y, z){// read one square of Turing machine tape
    L_obj v = read_record();
    if (v < 0) return v;
    return read_expr(0);
}
PROC(p_read_bit, x, y, z){ //read one square of Turing machine tape
    return read_bit();
}
PROC(p_bits, x, y, z){
    L_obj v,q;
    v = q = cons(NIL,NIL); 
    q=write_lst(x,q); write_chr('\n',q);
    return Cdr[v];
    /* read lisp s-expression from Turing machine tape, *
     * 8 bits per char                                  */
}
PROC(p_quit, x, y, z){
    termination_msg();
    return NIL;
}
PROC(p_load, x, y, z){
    char fname[200];
    FILE *fp, *instrm_prev;
    L_obj lfname;
    if(is_atom(x))
    {
        atm_ncpy(x,fname,200);
        lfname=mk_atom(0,fname,0);
        if((fp=fopen(fname,"r"))==NULL){
            return cons(mk_atom(0,"file-open-error",0),
                        cons(lfname,NIL));
        }
        instrm_prev=get_InputStream();
        set_InputStream(fp);
        while( io_flow() );
        fclose(fp);
        set_InputStream(instrm_prev); /* restore InputStream */

        return cons(mk_atom(0,"file-loaded",0),
                    cons(lfname,NIL));
    }
    return NIL; //dummy
}
PROC(p_show_strg, x, y, z){
    return mk_numb_from_long(show_next_node());
}
PROC(p_show_tree, x, y, z){
    printf("%-12s\n","show-tree");
    return out_tree(x);return cons(x,y);
}
PROC(p_show_atom, x, y, z){
    /* ( (object_node, its biding node) 
          object_no. 
          total_number_of_objects )*/
    char msga[80];
    strcpy(msga,"object:\n");
    strcat(msga,"((<node_no.>, <binding>)");
    strcat(msga," <atom_no.> <total_num_of_atoms>)");
    printf("%s\n",msga);
    return out(" --->", find_word_in_obj_lst(x));
}
PROC(p_show_all_atoms, x, y, z){
    return obj_lst_get();
}
PROC(p_help, x, y, z){
    return append(show_keywords(), 
                  cons(mk_atom(0,"keywords",0),NIL));
}

