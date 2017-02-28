/*---------------------------------------------------------/
 *  OUT.C
 *  ( in(1,0) によって作られた)Lisp式を表現するリスト構造に
 *  対応するS-式を出力する。
 *--------------------------------------------------------*/

#include "lisp_mt.h"
#include <string.h>

static void out_lst(L_obj x);
static void out_chr(L_obj x,int clmnflag);
static void out_atm(L_obj x,int clmnflag);

/*--- OUTPUT LISP-TREE ------------------------------*/
#define SPMAX 200
static char branches[SPMAX];
static char *tail;

static void init_branches(void);
static char *push_to_branches(char *s);
static char *rm_from_branches(size_t n);
static void tree(L_obj x, char flag);

static void init_branches(void)
{
    branches[0]='\0'; tail=branches;
}

static char *push_to_branches(char *s)
{
    int i=SPMAX-(tail-branches);

    i=(strlen(s)>i? i:strlen(s));
    strncat(branches,s,i);
    tail+=i;
    return tail;
}

static char *rm_from_branches(size_t n)
{
    int i=tail-branches-n;
    tail=branches+(i>0? i:0);
    *tail='\0';
    return tail;
}

static void prn_atm(L_obj x)
{
    /* It should be noticed that when "0" or "00..0" is read *  
     * it is replaced with mk_numb(NIL) in this Lisp.        */
    if( is_numb(x) && Pname[x]==NIL )
    {
        putchar('0'); return;
    }
    out_atm(Pname[x],1);
}

static void tree(L_obj x, char flag)
{
    if(is_atom(x))
    {
        putchar(' '); prn_atm(x); putchar('\n');
    }
    else
    {
        if( Cdr[x]==NIL && flag==1 ) printf("'--");
        else if(flag==0)             printf(".--");
        else                         printf("+--");

        if( !is_atom(Car[x]) )
        {
            if( Cdr[x]!=NIL )
                push_to_branches("|  ");
            else
                push_to_branches("   ");
        }
        tree(Car[x],0);
        if( !is_atom(Car[x]) ) rm_from_branches(3);
    }

    if( !is_atom(Cdr[x]) )
    {
        printf("%s|\n",branches);
        printf("%s",branches);
        tree(Cdr[x],1);
    }
}

L_obj out_tree(L_obj x)
{
    init_branches();
    /* put some blank at the front of lines */
    printf(" `");
    push_to_branches("  ");

    tree(x,0);
    return x;
}
/*---------------------------------------------------*/

L_obj out(char *x, L_obj y) /* output expression */
{
    printf("%-12s",x);
    Col = 0; /* so can insert \n and 12 blanks
                every "COLMAX" characters of output */
    out_lst(y);
    printf("\n");
    return y;
}
 
static void out_lst(L_obj x) /* output list */
{
    if (is_numb(x) && Pname[x] == NIL) {out_chr('0',1); return;} 
    /* null list of digits means zero */
    if (is_atom(x)) 
    {    
        out_atm(Pname[x],1);
        return;
    }
    out_chr('(',1);
    while (!is_atom(x)) 
    {
        out_lst(Car[x]);
        x = Cdr[x];
        if (!is_atom(x)) out_chr(' ',1);
    }
    out_chr(')',1);
}
 
static void out_atm(L_obj x,int clmnflag) /* output atom */
{
    if (x == NIL) return;
    /* output characters in reverse order */
    out_atm(Cdr[x],clmnflag);
    out_chr(Car[x],clmnflag);
}
 
static void out_chr(L_obj x, int clmnflag) /* output character */
{
    if (clmnflag && Col++ == COLMAX) {printf("\n%-12s"," ");  Col = 1;}
    putchar(x);
}

static int atm_ncpy_iter(L_obj x, char *p, int len)
{
    int i;
    if(x == NIL || len<=1)return 0;
    i=atm_ncpy_iter(Cdr[x],p,--len);
    *(p+i)=Car[x];
    return ++i;
}

int atm_ncpy(L_obj x, char str[], int len)
{
    int i;
    i=atm_ncpy_iter(Pname[x], str, len-1);
    str[i]='\0';
    return i;  
}
