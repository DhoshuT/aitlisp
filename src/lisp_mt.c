/*--------------------------------------------------------*
 * lisp_mt.c:                                             * 
 *      high-speed LISP interpreter by G.J. Chaitin       *
 *                                  Modified by M. Takama *
 *--------------------------------------------------------*/

/*
 *  To compile, type
 *     make
 *  To run interactively, type
 *     lisp
 *  To run with output on screen, type
 *     lisp <test.l
 *  To run with output in file, type
 *     lisp <test.l >test.r
 *
 *  Reference:  Kernighan & Ritchie,
 *  The C Programming Language, Second Edition,
 *  Prentice-Hall, 1988.
 */

#define GLOBAL_VALUE_DEFINE
#include "lisp_mt.h"
#include "proc.h"

int main() /* lisp main program */
{
    Time1 = time(NULL); /* start timer */
    Next=0; Col=0; Obj_lst=NIL;

    printf("LISP Interpreter Run\n");
#ifndef ORIG_C
    printf("(\"define\" differs from Chaitin's original)\n");
#endif
    initialize_atoms();
 
    set_InputStream(stdin);
    while( io_flow() );

    return 0;
}
 
int io_flow(void)
{
    L_obj e, f, name, def;

    printf("\n");
    /* read lisp meta-expression, ) not okay */
    e = in(1,0);
    printf("\n");
    f = Car[e];
    name = Car[Cdr[e]];
    def = Car[Cdr[Cdr[e]]];
    /* definition */
    if (f == wrd_define) 
    {
        if (is_atom(name)) 
        {
        /* variable definition, e.g., define x (a b c) */
#ifndef ORIG_C
            def = ev(def); /* which differs from the original*/
#endif
        } /* end of variable definition */
        else
        { /* function definition, e.g., define (F x y) cons x cons y nil */
            L_obj var_list = Cdr[name];
            name = Car[name];
            def = cons(wrd_lambda,cons(var_list,cons(def,NIL)));
        }  /* end of function definition */
        out("define",name);
        out("value",def);
#ifdef TREE_EXP
        out_tree(def);
#endif
        /* new binding replaces old */
        Car[Vlst[name]] = def;
        return 1;
    }

    if( e==wrd_find_EOF )
    {
        if(get_InputStream()!=stdin)
        {
             out("find-EOF",wrd_load);
             return 0;
        }
        termination_msg();
        return 0;
    }

    out("expression",e);
#ifdef TREE_EXP
    if( !is_atom(e) ) out_tree(e);
#endif

    /* evaluate expression */
    e=out("value",ev(e));
#ifdef TREE_EXP
    if( !is_atom(e) ) out_tree(e);
#endif
    return 1;
}

void termination_msg(void)
{
    Time2 = time(NULL);
    printf("End of LISP Run\n");
    printf("\tElapsed time is %.0f seconds.\n",
           difftime(Time2,Time1));
    /* on some systems, above line should instead be: *
     * Time2 - Time1                                  */
    printf("\tStrage: %ld nodes were used.\n",show_next_node());
}

void initialize_atoms(void) /* initialize atoms */
{
    if ( NIL != mk_atom(0,"()",0) ) {
       printf("nil != 0\n");
       exit(0); /* terminate execution */
    }

    register_atoms();

    Car[Vlst[wrd_nil]] = NIL; /* so that value of nil is () */

    wrd_zero = mk_numb(NIL);
    wrd_one = mk_numb(cons('1',NIL));
    
    register_aliases();

    begin_comment=Pname[left_bracket];
    end_comment  =Pname[right_bracket];
}

L_obj mk_pre_atom()
{
    L_obj a;
    a = cons(NIL,NIL); /* get an empty node */
    Car[a] = Cdr[a] = a; /* so that car & cdr of atom = atom */
    chk_atom(a);
    return a;
}
L_obj mk_atom(short number, char *name, short args) /* make an atom */
{
    L_obj a = mk_pre_atom();
    unchk_numb(a);
    Pname[a] = mk_string(name);
    Pf_numb[a] = number;
    Pf_args[a] = args;
    /* initially each atom evaluates to self */
    Vlst[a] = cons(a,NIL);
    /* put on object list */
    obj_lst_add(a);
    return a;
}

L_obj mk_numb(L_obj value) /* make an number */
{ /* digits are in reverse order, and 0 has empty list of digits */
    L_obj a = mk_pre_atom();
    chk_numb(a);
    Pname[a] = value; /* must make 00099 into 99 and 000 into empty list of digits */
    /* if necessary before calling this routine 
      (to avoid removing leading zeros unnecessarily) */
    Pf_numb[a] = 0;
    Pf_args[a] = 0;
    Vlst[a] = 0;
    /* do not put on object list ! */
    return a;
}
 
L_obj mk_alias(char *alas_nm, L_obj target_atm)
{
    L_obj a = mk_pre_atom();
    unchk_numb(a);
    Pname[a] = mk_string(alas_nm);
    Pf_numb[a] = 0;
    Pf_args[a] = 0;
    /* initially each atom evaluates to self */
    Vlst[a] = cons(target_atm,NIL);
    /* put on object list */
    obj_lst_add2(a,target_atm);
    return a;
}

L_obj mk_string(char *p) /* make list of characters */
{             /* in reverse order */
    L_obj v = NIL;
    while (*p != '\0')
        v = cons(*p++,v);
    return v;
}
 
L_obj cons(L_obj x, L_obj y) /* get free node & stuff x & y in it */
{
    L_obj z;
    
    /* if y is not a list, then cons is x */
    if ( y != NIL && is_atom(y) ) return x;
    
    if (show_next_node() >= SIZE) {
        printf("Storage overflow!\n");
        exit(0);
    }
 
    z = get_next_node();
    Car[z] = x;
    Cdr[z] = y;
    unchk_atom(z);
    unchk_numb(z);
    Pname[z] = 0;
    Pf_numb[z] = 0;
    Pf_args[z] = 0;
    Vlst[z] = 0;
 
    return z;
}

