/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

using namespace std;

UnlimitedInt* cal_gcd(UnlimitedInt* p, UnlimitedInt* q){
    bool c = 1;
    bool e = 1;
    UnlimitedInt* temp;
    while(c){
        temp = p;
        p = q;
        q = UnlimitedInt::mod(temp,q);
        bool d = 1;
        for(int i = 0; i<q->get_size();i++){
            if (q->get_array()[i]!=0){
                d = 0;
            }
        }
        if (d){
            c = 0;
        }
    }
    return p;
}

UnlimitedRational* simplify(UnlimitedRational* f){
    UnlimitedInt* gcd = cal_gcd(f->get_p(), f->get_q());
    return new UnlimitedRational(UnlimitedInt::div(f->get_p(), gcd), UnlimitedInt::div(f->get_q(), gcd));
}

UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt("1");
    q = new UnlimitedInt("1");
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p = num;
    q = den;
    UnlimitedInt* m_one = new UnlimitedInt("-1");
    UnlimitedInt* gcd;
    if (p->get_sign()==1 and q->get_sign()==1){
        gcd = cal_gcd(p, q);
    }
    else if (p->get_sign()==-1 and q->get_sign()==1){
        gcd = cal_gcd(UnlimitedInt::mul(p,m_one), q);
    }
    else if (p->get_sign()==1 and q->get_sign()==-1){
        gcd = cal_gcd(p, UnlimitedInt::mul(q,m_one));
    }
    else{
        gcd = cal_gcd(UnlimitedInt::mul(p,m_one), UnlimitedInt::mul(q,m_one));
    }
    p = UnlimitedInt::div(p,gcd);
    q = UnlimitedInt::div(q,gcd);
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    return p->to_string() + '/' + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::add(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
    UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::sub(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
    UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::mul(p1,p2);
    UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::mul(p1,q2);
    UnlimitedInt* den = UnlimitedInt::mul(q1,p2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}