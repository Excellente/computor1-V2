#ifndef COMPV1_H
#define COMPV1_H

#include "term.hpp"
#include "common.hpp"

#define REGX_POLYNOM 0
#define REGX_TERM 1

typedef vector<Term>::iterator v_iter_t;

class Computor{

    private:
        int _err;
        Term *_t;
        string _tmp;
        string _lhs;
        string _rhs;
        string _exp;
        int _hpower;
        vector<Term> _exp_terms;

    public:
        ~Computor();
        Computor(string e);

        // io functions
        void output_result();
        void debugmode(string debug);
        template <class T>
        size_t count_terms(vector<T> v);
        void print_terms(vector<Term> v);
        bool iformat(const string &t, int f);
        
        // term construction functions
        void init();
        void assign_term();
        void _sign(string &_e, int &last, int &sign);
        void string_2_term(string _e, int &sign, int f);
        void lead_sign(string &p, int &_sign, int &last);
        vector<string> strsplit(const string &del) const;
        void get_term(const string &_exp, int &f, int &l);
        
        // solving functions
        void solve();
        void transpose();
        void add_like_terms();
        bool ignore(vector<float> del, float _exp);
        void reduce(vector<Term> &lt, v_iter_t bvi, v_iter_t evi);
    };

#endif