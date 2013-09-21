#include "stmath.h"

STMath::STMath()
{
}

MatData * STMath::createOrthExpPlan(int num, int level) {
    if (level == 3)
        return createThreeLevelOrthPlan(num);
    else
        return createTwoLevelOrthPlan(num);
}

MatData * STMath::createTwoLevelOrthPlan(int n) {
    int i = 1, left = n;
    MatData * iPlan, * tPlan;
    while(1) {
        if (i==1) {
            iPlan = new MatData(2,1);
            iPlan->dat[0][0] = 1; iPlan->dat[1][0] = 2;
            tPlan = iPlan->copyMat();
        }
        else {
            MatData *t_iPlan = iPlan;
            iPlan = updatePlanTwoLevel(t_iPlan);
            delete t_iPlan;
            MatData *tmp = new MatData(tPlan->n*2,tPlan->m);
            for (int j=0;j<i;j++) {
                tmp->copyData(j*2,0,tPlan,j,0,1,tPlan->m);
                tmp->copyData(j*2+1,0,tPlan,j,0,1,tPlan->m);
            }
            MatData *nPlan = new MatData(tmp->n,tmp->m+iPlan->m);
            nPlan->copyData(0,0,tmp,0,0,tmp->n,tmp->m);
            nPlan->copyData(0,tmp->m,iPlan,0,0,iPlan->n,iPlan->m);
            delete tPlan;
            delete tmp;
            tPlan = nPlan;
        }
        left = left-i;
        if (left<1)
            break;
        i = i*2;
    }

    MatData * plan = tPlan->subMat(0,tPlan->n-1,tPlan->m-n,tPlan->m-1);
    delete iPlan;
    delete tPlan;
    return plan;
}

MatData * STMath::updatePlanTwoLevel(MatData *oPlan) {
    int n = oPlan->n, m = oPlan->m;
    MatData * nPlan = new MatData(n*2,m*2);
    MatData *tmp = new MatData(n,1);
    for (int i=0;i<m;i++) {
        tmp->copyData(0,0,oPlan,0,i,n,1);
        nPlan->copyData(0,i*2,tmp,0,0,n,1);
        nPlan->copyData(n,i*2,tmp,0,0,n,1);
        nPlan->copyData(0,i*2+1,tmp,0,0,n,1);
        for(int j=0;j<n;j++)
            tmp->dat[j][0] = 3-tmp->dat[j][0];
        nPlan->copyData(n,i*2+1,tmp,0,0,n,1);
    }
    delete tmp;
    return nPlan;
}

MatData * STMath::createThreeLevelOrthPlan(int n) {
    int i = 1, left = n;
    MatData * iPlan, * tPlan;
    while(1) {
        if (i==1) {
            iPlan = new MatData(3,1);
            iPlan->dat[0][0] = 1; iPlan->dat[1][0] = 2; iPlan->dat[2][0] = 3;
            tPlan = iPlan->copyMat();
        }
        else {
            MatData *t_iPlan = iPlan;
            iPlan = updatePlanThreeLevel(t_iPlan);
            delete t_iPlan;
            MatData *tmp = new MatData(tPlan->n*3,tPlan->m);
            for (int j=0;j<i;j++) {
                tmp->copyData(j*3,0,tPlan,j,0,1,tPlan->m);
                tmp->copyData(j*3+1,0,tPlan,j,0,1,tPlan->m);
                tmp->copyData(j*3+2,0,tPlan,j,0,1,tPlan->m);
            }
            MatData *nPlan = new MatData(tmp->n,tmp->m+iPlan->m);
            nPlan->copyData(0,0,tmp,0,0,tmp->n,tmp->m);
            nPlan->copyData(0,tmp->m,iPlan,0,0,iPlan->n,iPlan->m);
            delete tPlan;
            delete tmp;
            tPlan = nPlan;
        }
        left = left-i;
        if (left<1)
            break;
        i = i*3;
    }

    MatData * plan = tPlan->subMat(0,tPlan->n-1,tPlan->m-n,tPlan->m-1);
    delete iPlan;
    delete tPlan;
    return plan;
}

MatData * STMath::updatePlanThreeLevel(MatData *oPlan) {
    int n = oPlan->n, m = oPlan->m;
    MatData * nPlan = new MatData(n*3,m*3);
    MatData *tmp = new MatData(n,1);
    for (int i=0;i<m;i++) {
        tmp->copyData(0,0,oPlan,0,i,n,1);
        nPlan->copyData(0,i*3,tmp,0,0,n,1);
        nPlan->copyData(n,i*3,tmp,0,0,n,1);
        nPlan->copyData(n*2,i*3,tmp,0,0,n,1);
        nPlan->copyData(0,i*3+1,tmp,0,0,n,1);
        nPlan->copyData(0,i*3+2,tmp,0,0,n,1);
        for(int j=0;j<n;j++) {
            tmp->dat[j][0]++;
            if (tmp->dat[j][0]>3)
                tmp->dat[j][0] = 1;
        }
        nPlan->copyData(n,i*3+1,tmp,0,0,n,1);
        nPlan->copyData(n*2,i*3+2,tmp,0,0,n,1);
        for(int j=0;j<n;j++) {
            tmp->dat[j][0]++;
            if (tmp->dat[j][0]>3)
                tmp->dat[j][0] = 1;
        }
        nPlan->copyData(n,i*3+2,tmp,0,0,n,1);
        nPlan->copyData(n*2,i*3+1,tmp,0,0,n,1);
    }
    delete tmp;
    return nPlan;
}
