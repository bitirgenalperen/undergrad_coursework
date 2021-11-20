#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "the2.h"

double **initialize_the_data(int *row_count, int *row_size) {
    double var,**ptr=NULL,*t=NULL;
    int ele=0,k=1,rs = 1;
    ptr = malloc(sizeof(double *));
    t = malloc(sizeof(double));
    
    while(k){
            scanf("%lf",&var);
            if(var!=-1){
                t[ele++] = var;
                t = realloc(t,sizeof(double)*(++rs));
            }
            else{k=0;
                ptr[0]=t;
            }
    }
    
    k=2;
    while(k){
        scanf("%lf",&var);
        if(var!=-1){
            ptr = realloc(ptr,sizeof(double *)*(k));
            ptr[k-1] = malloc(sizeof(double)*(rs-1));
            ptr[k-1][0]=var;
            for(ele=1;ele<rs-1;ele++){
                scanf("%lf",&var);
                ptr[k-1][ele] = var;
            }
            k++;
            scanf("%lf",&var);
        }
        else{
            *row_count = k-1;
            k = 0;
        }
    }
    *row_size =rs-1;
    return ptr;
}

void print_first_n_row(double **matrix, int n, int row_size) {
    int row,ele;
    for(row=0;row<n;row++){
        for(ele=0;ele<row_size;ele++){
            printf("%.4f",matrix[row][ele]);
            if((ele+1)!=row_size){printf(" ");}
        }
        if((row+1)!=n){printf("\n");}
    }
}

void calculate_dot_product(double **matrix, int row_size, int row1, int row2) {
    double product=0,*r1=NULL,*r2=NULL;
    int i;
    r1 = malloc(sizeof(double)*row_size);
    r2 = malloc(sizeof(double)*row_size);
    
    for(i=0;i<row_size;i++){
        r1[i] = matrix[row1][i];
        r2[i] = matrix[row2][i];
    }
    for(i=0;i<row_size;i++){
        product+=r1[i]*r2[i];
    }
    printf("Dot product of rows %d, %d: %.4f",row1,row2,product);
}

double **calculate_covariance_matrix(double **matrix, int row_count, int row_size) { 
    double *mean=NULL,int_mean,**cov=NULL,*t=NULL,int_pro;
    int i,j,k;
    
    mean = malloc(sizeof(double)*row_size);
    for(i=0;i<row_size;i++){
        int_mean = 0;
        for(j=0;j<row_count;j++){
            int_mean += matrix[j][i]; 
        }
        mean[i] = int_mean/(row_count);
    }
    
    cov = malloc(sizeof(double *)*row_count);
    t = malloc(sizeof(double)*row_size);
    cov[0]=t;
    for(i=1;i<row_count;i++){
        cov[i] = malloc(sizeof(double)*row_size);
    }
    
    for(i=0;i<row_size;i++){
        for(j=0;j<row_count;j++){
            int_pro = 0;
            for(k=0;k<row_count;k++){
                int_pro += (matrix[k][i]-mean[i])*(matrix[k][j]-mean[j]);   
            }
            cov[j][i] = int_pro/(row_count-1);
        }
    }
	return cov; }

double **calculate_x_transpose_times_x(double **matrix, int row_count, int row_size) { 
    double **prod=NULL,*t=NULL,int_pro=0,**atr=NULL,*s=NULL;
    int i,j,k;
    
    atr = malloc(sizeof(double *)*row_size);
    s = malloc(sizeof(double)*row_count);
    atr[0]=s;
    for(i=1;i<row_size;i++){
        atr[i] = malloc(sizeof(double)*row_count);
    }
    
    prod = malloc(sizeof(double *)*row_size);
    t = malloc(sizeof(double)*row_size);
    prod[0]=t;
    for(i=1;i<row_size;i++){
        prod[i] = malloc(sizeof(double)*row_size);
    }

    for(i=0;i<row_count;i++){
        for(j=0;j<row_size;j++){
            atr[j][i] = matrix[i][j];
        }
    }
    
    for (i = 0; i < row_size; i++) {
      for (j = 0; j < row_count; j++) {
        for (k = 0; k < row_count; k++) {
          int_pro += atr[i][k]*matrix[k][j];
        }
        prod[i][j] = int_pro;
        int_pro = 0;
      }
    }
    return prod; }

int check(double *p,double n,int k){
    int i;
    for(i=0;i<k;i++){
        if(p[i]==n){return 0;}
    }
    return 1;
}


double **group_by(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation) { 
    double **ptr=NULL,*t=NULL,*g=NULL;
    int i,j,k=1,ele,tg;
    double int_pro;
    
    
    g = malloc(sizeof(double));
    g[0] = matrix[0][group_column];;
    
    for(i=1;i<row_count;i++){
        if(check(g,matrix[i][group_column],k)){
            g = realloc(g,sizeof(double)*(++k));
            g[k-1] = matrix[i][group_column]; 
        }
    }
    group_count[0] = k;
    
    ptr = malloc(sizeof(double *)*k);
    t = malloc(sizeof(double)*row_size);
    ptr[0]=t;
    ptr[0][group_column] = g[0];
    for(i=1;i<k;i++){
        ptr[i] = malloc(sizeof(double)*row_size);
        ptr[i][group_column] = g[i] ;
    }
    
    
    if(operation == 0){
        
        for(i=0;i<k;i++){
            for(ele=0;ele<group_column;ele++){
                int_pro=0;
                for(j=0;j<row_count;j++){
                    if(matrix[j][group_column]==g[i]){int_pro += matrix[j][ele];}}
                    ptr[i][ele]=int_pro;}
            
            for(ele=group_column+1;ele<row_size;ele++){
                int_pro=0;
                for(j=0;j<row_count;j++){
                    if(matrix[j][group_column]==g[i]){int_pro += matrix[j][ele];}}
                    ptr[i][ele]=int_pro;}
        }
    }
    
    else if(operation ==1){
                
        for(i=0;i<k;i++){
            for(ele=0;ele<group_column;ele++){
                    int_pro=0;
                    tg=1;
                    for(j=0;j<row_count;j++){
                        if(matrix[j][group_column]==g[i]){int_pro += matrix[j][ele];
                            tg++;
                        }
                    }
                    ptr[i][ele]=int_pro/(tg-1);
                }

            
            for(ele=group_column+1;ele<row_size;ele++){
                    int_pro=0;
                    tg=1;
                    for(j=0;j<row_count;j++){
                        if(matrix[j][group_column]==g[i]){int_pro += matrix[j][ele];
                            tg++;
                        }
                    }
                    ptr[i][ele]=int_pro/(tg-1);;
                }
            }
        }
        
    
    else if(operation ==2){
        for(i=0;i<k;i++){
            for(ele=0;ele<group_column;ele++){
                int_pro=-999999;
                for(j=0;j<row_count;j++){
                    if((matrix[j][group_column]==g[i])&&(matrix[j][ele]>int_pro)){int_pro = matrix[j][ele];}}
                    ptr[i][ele]=int_pro;}
            
            for(ele=group_column+1;ele<row_size;ele++){
                int_pro=-999999;
                for(j=0;j<row_count;j++){
                    if((matrix[j][group_column]==g[i])&&(matrix[j][ele]>int_pro)){int_pro = matrix[j][ele];}}
                    ptr[i][ele]=int_pro;}
        }
    }
    
    else if(operation ==3){
        for(i=0;i<k;i++){
            for(ele=0;ele<group_column;ele++){
                int_pro=999999;
                for(j=0;j<row_count;j++){
                    if((matrix[j][group_column]==g[i])&&(matrix[j][ele]<int_pro)){int_pro = matrix[j][ele];}}
                    ptr[i][ele]=int_pro;}
            
            for(ele=group_column+1;ele<row_size;ele++){
                int_pro=999999;
                for(j=0;j<row_count;j++){
                    if((matrix[j][group_column]==g[i])&&(matrix[j][ele]<int_pro)){int_pro = matrix[j][ele];}}
                    ptr[i][ele]=int_pro;}
        }
    }
    
    return ptr; }


double **convolution(double **matrix, int row_count, int row_size, double **kernel, int kernel_height, int kernel_width) { 
    double **con=NULL,*ct=NULL,int_pro;
    int i,j,k,m;
    
    con = malloc(sizeof(double *)*(row_count-kernel_height+1));
    ct = malloc(sizeof(double)*(row_size-kernel_width+1));
    con[0] = ct;
    for(i=1;i<row_count-kernel_height+1;i++){
        con[i] = malloc(sizeof(double)*(row_size-kernel_width+1));}
    for(i=0;i<row_count-kernel_height+1;i++){
        for(j=0;j<row_size-kernel_width+1;j++){
            for(k=0;k<kernel_height;k++){
                for(m=0;m<kernel_width;m++){
                int_pro+=kernel[k][m]*matrix[k+i][m+j] ;
                }
            }
            con[i][j] = int_pro;
            int_pro=0;
        }
    }
    return con;}
