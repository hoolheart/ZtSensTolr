#ifndef STMATH_H
#define STMATH_H

class MatData {
public:
    int n;
    int m;
    double ** dat;
    MatData(int _n, int _m) {
        n = _n>0?_n:0;
        m = _m>0?_m:0;
        if (n>0 && m>0) {
            dat = new double*[n];
            for (int i=0;i<n;i++)
                dat[i] = new double[m];
        }
        else
            dat = (double **)0;
    }
    ~MatData() {
        if (n>0 && m>0) {
            for (int i=0;i<n;i++)
                delete dat[i];
            delete dat;
        }
    }
    void fill(double d) {
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                dat[i][j] = d;
    }
    MatData * subMat(int n1, int n2, int m1, int m2) {
        n1 = n1>0?n1:0;
        n2 = n2<n?n2:(n-1);
        m1 = m1>0?m1:0;
        m2 = m2<m?m2:(m-1);
        if (n1<=n2 && m1<=m2) {
            MatData *t = new MatData(n2-n1+1,m2-m1+1);
            for (int i=n1;i<=n2;i++)
                for (int j=m1;j<=m2;j++)
                    t->dat[i-n1][j-m1] = dat[i][j];
            return t;
        }
        else
            return new MatData(0,0);
    }
    MatData * copyMat() {
        return subMat(0,n-1,0,m-1);
    }
    void copyData(int r1,int c1,MatData *s,int r2,int c2,int _n,int _m) {
        r1 = r1>0?r1:0; c1 = c1>0?c1:0;
        r2 = r2>0?r2:0; c2 = c2>0?c2:0;
        _n = (r1+_n<=n)?_n:(n-r1); _n = (r2+_n<=s->n)?_n:(s->n-r2);
        _m = (c1+_m<=m)?_m:(m-c1); _m = (c2+_m<=s->m)?_m:(s->m-c2);
        for (int i=0;i<_n;i++)
            for (int j=0;j<_m;j++)
                dat[r1+i][c1+j] = s->dat[r2+i][c2+j];
    }
};

class STMath
{
public:
    STMath();
    static MatData * createOrthExpPlan(int num, int level);
private:
    static MatData * createTwoLevelOrthPlan(int n);
    static MatData * updatePlanTwoLevel(MatData * oPlan);
    static MatData * createThreeLevelOrthPlan(int n);
    static MatData * updatePlanThreeLevel(MatData * pre);
};

#endif // STMATH_H
