#include "computor.hpp"

Computor::Computor(string exp) : _exp(exp){
    _hpower = 0;
}

Computor::~Computor(){
}

void Computor::solve()
{
    init();
    transpose();
    add_like_terms();
    print_terms(_exp_terms);
}

void Computor::add_like_terms()
{
    vector<Term> lt;
    vector<float> ig;
    v_iter_t evi = _exp_terms.end();
    v_iter_t bvi = _exp_terms.begin();

    for (; bvi != evi;)
    {
        if (!ignore(ig, bvi->getExponent()))
        {
            reduce(lt, bvi, evi);
            ig.push_back(bvi->getExponent());
        }
        bvi++;
    }
    _exp_terms = lt;
}

void Computor::reduce(vector<Term> &lt, v_iter_t bvi, v_iter_t evi)
{
    static int i;
    v_iter_t tmp;
    v_iter_t hit;

    lt.push_back(*bvi);
    for (tmp = bvi + 1; tmp != evi;)
    {
        if (bvi->getExponent() == tmp->getExponent())
        {
            lt[i] += *tmp;
            hit = tmp;
        }
        tmp++;
    }
    i++;
}

bool Computor::ignore(vector<float> del, float _exp)
{
    vector<float>::iterator bvi = del.begin();
    vector<float>::iterator evi = del.end();

    for (; bvi != evi; bvi++)
    {
        if (_exp == *bvi)
            return (true);
    }
    return (false);
}

void Computor::init()
{
    vector<string> ret;

    if (!iformat(_exp, REGX_POLYNOM))
    {
        cerr << "Error: InvalidInputFormat\n";
        exit(EXIT_FAILURE);
    }
    ret = strsplit("=");
    if (count_terms(ret) > 2)
    {
        cerr << "Error: InvalidInputFormat\n";
        exit(EXIT_FAILURE);
    }
    _lhs = ret[0];
    _rhs = ret[1];
}

void Computor::transpose()
{
    int sign;

    sign = 0;
    string_2_term(_lhs, sign, 0);
    sign = 0;
    string_2_term(_rhs, sign, 1);
}

void Computor::string_2_term(string _e, int &sign, int f)
{
    int last;
    int first;

    last = first = 0;
    while (_e[last] != '\0')
    {
        _sign(_e, last, sign);
        if (f == 1)
        {
            if (sign == 1)
                sign = 0;
            else
                sign = 1;
        }
        _t = new Term(sign);
        get_term(_e, first, last);
        assign_term();
        _exp_terms.push_back(*_t);
    }
}

void Computor::get_term(const string &_exp, int &first, int &last)
{
    while (_exp[last] != '+' && _exp[last] != '-' && _exp[last] != '\0')
        last++;
    _tmp = _exp.substr(first, last - first);
    if (_exp[last] != '\0')
        last++;
    first = last;
    if (!iformat(_tmp, REGX_TERM))
    {
        cerr << "Error: InvalidInputFormat\n";
        exit(EXIT_FAILURE);
    }
}

void Computor::assign_term()
{
    string::size_type sz;
    
    _t->setCoefficient(stof(_tmp, &sz));
    if (_tmp.find("X") == string::npos && _tmp.find("x") == string::npos);
    else
    {
        while (_tmp[sz] == ' ' || _tmp[sz] == '*') sz++;
        _t->setBase(_tmp.substr(sz, 2)[0]);
        if (_tmp.find("^") == string::npos)
            _t->setExponent(1.0f);
        else
        {
            sz++;
            while (_tmp[sz] == ' ' || _tmp[sz] == '^') sz++;
            _t->setExponent(stof(_tmp.substr(sz, 4), &sz));
        }
    }
}

void Computor::_sign(string &_e, int &last, int &sign)
{
    if (last > 0)
    {
        if (_e[last - 1] == '+')
            sign = 0;
        else if (_e[last - 1] == '-')
            sign = 1;
    }
    else
        lead_sign(_e, sign, last);
}

void Computor::lead_sign(string &p, int &_sign, int &last)
{
    int numsign;
    
    while (!(p[last] >= 48 && p[last] <= 57) && p[last] != '\0')
    {
        if (p[last] == '+' || p[last] == '-')
        {
            if (p[last] == '-')
                _sign = 1;
            else
                _sign = 0;
            if ((numsign += 1) > 1)
                _err = 1;
            
        }
        last++;
    }
    p = p.substr(last, string::npos);
}

void Computor::print_terms(vector<Term> v)
{
    int len = count_terms(v);

    for (int j = 0; j < len; j++)
        v[j].toString(j);
    cout << endl;
}

template <class T>
size_t Computor::count_terms(vector<T> v)
{
    size_t terms;
    typename vector<T>::iterator evi = v.end();
    typename vector<T>::iterator bvi = v.begin();

    terms = 0;
    while (bvi != evi)
    {
        bvi++;
        terms++;
    }
    return (terms);
}

bool Computor::iformat(const string &t, int f)
{
    regex r0("(.+)(\\s)=(\\s)(.+)");    
    regex r1("(\\s+)?((-|\\+)(\\s+)?)?[[:digit:]]+(\\.[[:digit:]]+)?((\\s(\\*\\s)?)?(X|x)((\\s)?(\\^(\\s)?[[:digit:]]+))?)?(\\s)?");

    if (f == REGX_POLYNOM)
    {
        if (regex_match(t, r0))
            return (true);
    }
    else if (f == REGX_TERM)
    {
        if (regex_match(t, r1))
            return (true);
    }
    return (false);
}

vector<string> Computor::strsplit(const string &del) const
{
    int len;
    size_t pos;
    vector<int> delpos;
    vector<string> terms;

    len = 0;
    for (int i = 0; i != string::npos;)
    {
        delpos.push_back((i = _exp.find(del, i + 1)));
        len++;
    }
    terms.push_back(_exp.substr(0, delpos[0]));
    for (int i = 1; i < len; i++)
        terms.push_back(_exp.substr(delpos[i - 1] + 1, (delpos[i] - delpos[i - 1]) - 1));
    return (terms);
}

// void Computor::debugmode(string debug)
// {
//     int len = count_terms(_CBA);

//     cout <<"========== Entered debug mode ==========" << endl;
//     if (debug.compare("-d") == 0)
//         cout << "discriminant = " <<_discrimi << endl;
//     else if (debug.compare("-abc") == 0)
//     {
//             cout
//                 << "a = " << _CBA[2]
//                 << ", b = " << _CBA[1]
//                 << ", c = " << _CBA[0] <<
//             endl;

//     }
//     else if (debug.compare("-dabc") == 0)
//     {
//         cout << "discriminant = " <<_discrimi << endl;
//         cout
//             << "a = " << _CBA[2]
//             << ", b = " << _CBA[1]
//             << ", c = " << _CBA[0] <<
//         endl;
//     }
//     else
//         cout << "ERROR: Debug text " << debug << endl;
// }