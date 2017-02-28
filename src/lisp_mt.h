/*--------------------------------------------------------*
 * lisp_mt.h:                                             * 
 *      high-speed LISP interpreter by G.J. Chaitin       *
 *                                  Modified by M. Takama *
 *--------------------------------------------------------*/

/*
 *  The storage required by this interpreter is 
 *       6 * 4 + 2 = 26 bytes 
 *  times the symbolic constant SIZE, which is 
 *       26 * 5,000,000 = 130 megabytes.
 *  To run this interpreter in small machines,
 *  reduce the #define SIZE 1000000 below.
 */

#ifndef H_LISP_MT
#define H_LISP_MT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*---------------------------------------------*/
#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
#else
#define GLOBAL extern
#endif
/*---------------------------------------------*/

typedef long L_obj;  /* universal type using for objects in this lisp*/
#define SIZE 5000000 /* numbers of nodes of tree storage */
#define NIL 0 /* end of list marker */

GLOBAL L_obj Car[SIZE], Cdr[SIZE]; /* tree storage */
GLOBAL char Atom[SIZE]; /* is it an atom? */

#define chk_atom(node)   Atom[node]=1
#define unchk_atom(node) Atom[node]=0
#define is_atom(node) Atom[node]

GLOBAL unsigned char Numb[SIZE]; /* is it a number? */
#define chk_numb(node)   Numb[node]=1
#define unchk_numb(node) Numb[node]=0
#define is_numb(node) Numb[node]

/* The following is only used for atoms */
GLOBAL L_obj Vlst[SIZE];  /* bindings of each atom */
GLOBAL L_obj Pname[SIZE]; /* print name of each atom
                             = list of characters in reverse */

#define is_zero(node) (Numb[node] && Pname[node]==NIL)

/* The following is only used for atoms that are the names of 
   primitive functions */
/* primitive function number (for interpreter switch) */
GLOBAL short Pf_numb[SIZE];
GLOBAL short Pf_args[SIZE]; /* number of arguments + 1 (for input parser) */
                            /* the number of arguments must be <=3 */
#define is_regfunc(atom) (0 < Pf_numb[(atom)] && Pf_numb[(atom)] <= MAX_REG_PROCS)

/* list of all atoms (& every other token read except numbers) */
GLOBAL L_obj Obj_lst; 
#define obj_lst_add(a)      Obj_lst = cons(cons((a),cons((a),NIL)),Obj_lst)
#define obj_lst_add2(a,b)   Obj_lst = cons(cons((a),cons((b),NIL)),Obj_lst)
#define obj_lst_get()       Obj_lst
#define obj_lst_next(n)     Cdr[n]
#define get_atm_obj_lst(n)  Car[Car[(n)]]
#define get_atm2_obj_lst(n) Car[Cdr[Car[(n)]]]

/* locations of atoms in tree storage */
GLOBAL L_obj wrd_nil, wrd_true, wrd_false, wrd_define, \
             wrd_let, wrd_lambda, wrd_quote, wrd_if, \
             wrd_cons, wrd_eq, wrd_neq, wrd_lt, wrd_gt, wrd_le, wrd_ge, \
             wrd_add, wrd_times, wrd_power, wrd_sub, wrd_div, \
             wrd_append, wrd_atom, wrd_length, wrd_display, wrd_debug, \
             wrd_size, wrd_help;
GLOBAL L_obj wrd_remainder, wrd_show_strg ,wrd_show_tree, \
             wrd_quit, wrd_load, \
             wrd_show_atom, wrd_show_all_atoms;
GLOBAL L_obj wrd_car, wrd_cdr, wrd_caar, wrd_cadr, wrd_caddr, wrd_eval, wrd_try, \
             wrd_not, wrd_and, wrd_or, \
             wrd_base2_to_10, wrd_base10_to_2, \
             wrd_read_exp, wrd_bits, wrd_read_bit, wrd_run_utm_on;
GLOBAL L_obj wrd_no_time_limit, wrd_out_of_time, wrd_out_of_data, \
             wrd_success, wrd_failure, \
             wrd_division_with_zero;
GLOBAL L_obj left_bracket, right_bracket, left_paren, right_paren, \
             double_quote;
GLOBAL L_obj begin_comment, end_comment;
GLOBAL L_obj wrd_zero, wrd_one;
GLOBAL L_obj wrd_find_EOF;

GLOBAL L_obj Next; /* next free node */
#define show_next_node() Next
#define get_next_node()  Next++

GLOBAL FILE *InputStream;
#define set_InputStream(stream) InputStream=(stream)
#define get_InputStream()       InputStream

#define COLMAX 40

/* column in each "COLMAX" character chunk of output
   (preceeded by 12 char prefix) */
GLOBAL long Col;
GLOBAL time_t Time1; /* clock at start of execution */
GLOBAL time_t Time2; /* clock at end of execution */
/* stack of binary data for try's */
GLOBAL L_obj turing_machine_tapes;
/* stack of stubs to collect captured displays on */
GLOBAL L_obj display_enabled;
/* stack of flags whether to capture displays or not */
GLOBAL L_obj captured_displays;
/* buffer for converting lists of bits into s-expressions *
   contains list of all the words in an input record      */
GLOBAL L_obj Buffer2;

/* FUNCTIONS */
extern void  initialize_atoms(void); /* initialize atoms */
extern void  termination_msg(void);
extern int   io_flow(void); /* main routine */
extern L_obj mk_atom(short number, char *name, short args); /* make an atom */
extern L_obj mk_alias(char *alas_nm, L_obj atm);
extern L_obj mk_numb(L_obj value);   /* make an number */
extern L_obj mk_string(char *p);     /* make list of characters */
/* are two lists of characters equal ? */
extern L_obj eq_wrd(L_obj x, L_obj y);
extern L_obj lookup_word(L_obj x);   /* look up word in object list ? */
extern L_obj cons(L_obj x, L_obj y); /* get free node & stuff x & y in it */

extern L_obj out(char *mesg, L_obj y);  /* output expression */
extern int   atm_ncpy(L_obj x, char *str, int len);
extern L_obj out_tree(L_obj x);

/* are two lists of characters equal ? */
extern L_obj eq_wrd(L_obj x, L_obj y);
/* look up word in object list ? */
extern L_obj lookup_word(L_obj x);
/* input m-exp */
extern L_obj in(unsigned char mexp,unsigned char rparenokay);
/* check if list of characters are exclusively digits */
extern L_obj only_digits(L_obj x);

extern L_obj ev(L_obj e); /* initialize and evaluate expression */

extern L_obj append(L_obj x, L_obj y);  /* append two lists */
extern L_obj eq(L_obj x, L_obj y);      /* equal predicate */
extern L_obj length(L_obj x);           /* number of elements in list */
extern L_obj compare(L_obj x, L_obj y); /* compare two decimal numbers */
extern L_obj add1(L_obj x);             /* add 1 to decimal number */
extern L_obj sub1(L_obj x);             /* subtract 1 from decimal number */
extern L_obj nmb(L_obj x);              /* pick-up decimal number from atom 
                                           & convert non-number to zero */
/* from reversed list of digits of decimal number */
extern L_obj remove_leading_zeros(L_obj x);
/* add two decimal numbers */
extern L_obj addition(L_obj x, L_obj y, L_obj carry_in);
/* multiply two decimal numbers */
extern L_obj multiplication(L_obj x, L_obj y);
/* base raised to the power exponent */
extern L_obj power(L_obj base, L_obj exponent);
/* x - y assumes x >= y */
extern L_obj subtraction(L_obj x, L_obj y);
/* convert bit string to decimal number */
extern L_obj division(L_obj x, L_obj y);
#define quot(z) Car[z]
#define rem(z)  Cdr[z]
extern L_obj base2_to_10(L_obj x);
/* used to convert decimal number to bit string */
extern L_obj halve(L_obj x);
/* convert decimal number to bit string */
extern L_obj base10_to_2(L_obj x);
/* number of characters in print representation */
extern L_obj size(L_obj x);
/* read one square of Turing machine tape */
extern L_obj read_bit(void);
/* convert character into 8 bits */
extern L_obj write_chr(L_obj x,L_obj firstpt);
/* convert s-exp into list of bits */
extern L_obj write_lst(L_obj x,L_obj firstpt);
/* read record from Turing machine tape */
extern L_obj read_record(void);
/* read one character from Turing machine tape */
extern L_obj read_char(void);
/* read word from Turing machine tape */
extern L_obj read_word(void);
/* read s-exp from Turing machine tape */
extern L_obj read_expr(unsigned char rparenokay);

/* make a number from a long type number in C */
extern L_obj mk_numb_from_long(long num);
/*find word in object list */
extern L_obj find_word_in_obj_lst(L_obj x);

#endif









