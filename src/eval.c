/*---------------------------------------------------------/
 *  EVAL.C 
 *  ( in(1,0) によって作られた)Lisp式を表現するリスト構造を
 *  使ってLisp式を評価する。
 *--------------------------------------------------------*/

#include "lisp_mt.h"
#include "proc.h"

static L_obj eval(L_obj e, L_obj d);      /* evaluate expression */
static void clean_env(void);              /* clean environment */
static void restore_env(void);            /* restore unclean environment */
static void bind(L_obj vars, L_obj args); /* bind values of arguments
                                             to formal parameters */
static void unbind(L_obj vars);           /* retore binding values of 
                                             arguments to the previous ones*/
static L_obj evalst(L_obj e, L_obj d);    /* evaluate list of expressions */

L_obj ev(L_obj e) /* initialize and evaluate expression */
{
    L_obj v;
    turing_machine_tapes = cons(NIL,NIL);
    display_enabled = cons(1,NIL);
    captured_displays = cons(NIL,NIL);
    v = eval(e,wrd_no_time_limit);
    return (v < 0 ? -v : v);
}
 
static L_obj eval(L_obj e, L_obj d) /* evaluate expression */
{
   /*
    e is expression to be evaluated
    d is permitted depth - decimal integer, or wrd_no_time_limit
   */
    L_obj f, v, args, x, y, z, vars, body;
    
    if (is_numb(e)) return e;
    /* find current binding of atomic expression */
    if (is_atom(e)) return Car[Vlst[e]];
    
    f = eval(Car[e],d); /* evaluate function */
    e = Cdr[e]; /* remove function from list of arguments */
    if (f < 0) return f; /* function = error value? */
    
    if (f == wrd_quote) return Car[e]; /* quote */
    
    if (f == wrd_if) { /* if then else */
        v = eval(Car[e],d);
        e = Cdr[e];
        if (v < 0) return v; /* error? */
        if (v == wrd_false) e = Cdr[e];
        return eval(Car[e],d);
    }
    
    args = evalst(e,d); /* evaluate list of arguments */
    if (args < 0) return args; /* error? */
    
    x = Car[args]; /* pick up first argument */
    y = Car[Cdr[args]]; /* pick up second argument */
    z = Car[Cdr[Cdr[args]]]; /* pick up third argument */

    /* fが組み込み関数の場合 */
    if( is_regfunc(f) ){
        if (f == wrd_quit){ 
            proc_call(f, x, y, z); 
            exit(0);
        }
        return proc_call(f, x, y, z);
    }

    if (d != wrd_no_time_limit) {
        if (d == NIL) return - wrd_out_of_time; /* depth exceeded -> error! */
        d = sub1(d); /* decrement depth */
    }
    
    if (f == wrd_eval) {
        clean_env();   /* clean environment */
        v = eval(x,d);
        restore_env(); /* restore unclean environment */
        return v;
    }
    
    if (f == wrd_try) {
        L_obj stub, old_try_has_smaller_time_limit = 0; 
        /* assume normal case, that x < d */
        if (x != wrd_no_time_limit) x = nmb(x); /* convert s-exp into number */
        if ( (x == wrd_no_time_limit) || 
             (d != wrd_no_time_limit && compare(x,d) != '<')) 
        {  old_try_has_smaller_time_limit = 1;
           x = d; /* continue to use older more constraining time limit */
        }
        turing_machine_tapes = cons(z,turing_machine_tapes);
        display_enabled = cons(0,display_enabled);
        stub = cons(0,NIL); /* stub to grow list on */
        Car[stub] = stub; /* car of stub gives end of list */
        captured_displays = cons(stub,captured_displays);
        clean_env();
        v = eval(y,x);
        restore_env();
        turing_machine_tapes = Cdr[turing_machine_tapes];
        display_enabled = Cdr[display_enabled];
        stub = Cdr[Car[captured_displays]]; /* remove stub */
        captured_displays = Cdr[captured_displays];
        if (old_try_has_smaller_time_limit && v == - wrd_out_of_time)
            return v;
        if (v < 0)
            return cons(wrd_failure,cons(-v,cons(stub,NIL)));
        return cons(wrd_success,cons(v,cons(stub,NIL)));
    }
    
    f = Cdr[f];
    vars = Car[f];
    f = Cdr[f];
    body = Car[f];
    
    bind(vars,args);
    v = eval(body,d);
    unbind(vars); 

    return v;
}
 
static void clean_env(void) /* clean environment */
{
    L_obj o = obj_lst_get(), var;
    while (o != NIL) {
        var = get_atm_obj_lst(o);
        Vlst[var] = cons(var,Vlst[var]); /* everything eval's to self */
        o = Cdr[o];
    }
    Car[Vlst[wrd_nil]] = NIL; /* except that value of nil is () */
}
 
static void restore_env(void) /* restore unclean environment */
{
    L_obj o = obj_lst_get(), var;
    while (o != NIL) {
        var = get_atm_obj_lst(o);
        if (Cdr[Vlst[var]] != NIL){ /* was token read in by read-exp within a try */
            Vlst[var] = Cdr[Vlst[var]];
        }
        o = Cdr[o];
    } 
}
 
/* bind values of arguments to formal parameters */
static void bind(L_obj vars, L_obj args)
{
    L_obj var;
    if (is_atom(vars)) return;
    bind(Cdr[vars],Cdr[args]);
    var = Car[vars];
    if (is_atom(var))
        Vlst[var] = cons(Car[args],Vlst[var]);
}

/* retore binding values of arguments to the previous ones*/
static void unbind(L_obj vars)
{   L_obj var;
    while (!is_atom(vars)){
        var = Car[vars];
        if (is_atom(var))Vlst[var] = Cdr[Vlst[var]];
        vars = Cdr[vars];
    }
 }

/* evaluate list of expressions */
static L_obj evalst(L_obj e, L_obj d)
{
    L_obj x, y;
    if (e == NIL) return NIL;
    x = eval(Car[e],d);
    if (x < 0) return x; /* error? */
    y = evalst(Cdr[e],d);
    if (y < 0) return y; /* error? */
    return cons(x,y);
}
