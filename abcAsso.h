#include "abc.h"

typedef struct{

  double **stat;
  double **statOther; //for likelihood of other model added by emil 14-11-2018
  int **keepInd;
  int *highHe;
  int *highWt;
  int *highHo;
  double *betas; //for coefficients added by emil 07-11-2018
}assoStruct;



class abcAsso:public abc{
private:
  kstring_t bufstr;
public:
  //none optional stuff
  BGZF **multiOutfile;
  int doPrint;
  int minCov; //not for users
  int doMaf;
  int dynCov;//not for users
  int doAsso;
  int doPost;
  int GL;
  int sitePerm;  //not for users
  int isBinary;
  int minHigh;
  int minCount;
  int adjust;  //not for users
  int model;
  int mIter; //not for users
  double threshold; //not for users
  double hybridThres; //not for users
  
  void run(funkyPars  *pars);
  void print(funkyPars *pars);  
  void clean(funkyPars *pars);  
  void getOptions(argStruct *arguments);
  void printArg(FILE *argFile);

  abcAsso(const char *outfiles,argStruct *arguments,int inputtype);
  ~abcAsso();
  //other stuff
  char *covfile;
  char *yfile;
  
  angsd::Matrix<double> ymat;
  angsd::Matrix<double> covmat;
  void scoreAsso(funkyPars  *pars,assoStruct *assoc);
  double dosageAssoc(funkyPars *p,angsd::Matrix<double> *design,angsd::Matrix<double> *designNull,double *postOrg,double *yOrg,int keepInd,int *keepList,double freq,int s,assoStruct *assoc,int model, int isBinary, double* start, int fullModel);
  void dosageAsso(funkyPars  *pars,assoStruct *assoc);
  int getFitWLS(double* start, double* y, double** covMatrix, double* weights, int nInd3, int nEnv, int df);
  int getFitWLSBin(double* start, double* y, double** covMatrix, double* weights, int nInd3, int nEnv, int df);
  double logLike(double *start,double* y,angsd::Matrix<double> *design,double *post,int isBinary, int fullModel);
  double logupdateEM(double* start,angsd::Matrix<double> *design,angsd::Matrix<double> *postAll,double* y,int keepInd,double* post,int isBinary, int fullModel);
  double sd(double* phe, int size );
  double doEMasso(funkyPars *p,angsd::Matrix<double> *design,angsd::Matrix<double> *designNull,angsd::Matrix<double> *postAll,double *postOrg,double *yOrg,int keepInd,int *keepList,double freq,int s,assoStruct *assoc,int model, int isBinary, double* start, int fullModel);  
  void emAsso(funkyPars  *pars,assoStruct *assoc);
  void hybridAsso(funkyPars  *pars,assoStruct *assoc);
  void frequencyAsso(funkyPars  *pars,assoStruct *assoc);
  double doAssociation(funkyPars *pars,double *post,double *y,int keepInd,int *keepList,double freq,int s,assoStruct *assoc);
  int getFit(double *res,double *Y,double *covMatrix,int nInd,int nEnv);
  int getFitBin(double *res,double *Y,double *covMatrix,int nInd,int nEnv);
  double normScoreEnv(double *post,int numInds, double *y, double *ytilde,double *cov,int nEnv,double freq,assoStruct *assoc,int s);
  double binomScoreEnv(double *post,int numInds, double *y, double *ytilde,double *cov,int nEnv,double freq,assoStruct *assoc,int s);
  void printDoAsso(funkyPars *pars);
};
