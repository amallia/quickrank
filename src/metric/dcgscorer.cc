#include "metric/dcgscorer.h"

#include <cmath>

#define POWEROFTWO(p) ((float)(1<<((unsigned int)(p))))

double DCGScorer::compute_score(const qlist &ql) {
  if(ql.size<=0)
    return -1.0;
  const unsigned int size = (k>ql.size or k<=0) ? ql.size : k;
  float dcg = 0.0f;
  for(unsigned int i=0; i<size; ++i)
    dcg += (POWEROFTWO(ql.labels[i])-1.0f)/log2(i+2.0f);
  return dcg;
}
fsymmatrix* DCGScorer::swap_change(const qlist &ql) {
  fsymmatrix *changes = new fsymmatrix(ql.size);
  unsigned int size = ql.size<k ? ql.size : k;
#pragma omp parallel for
  for(unsigned int i=0; i<size; ++i) {
    double *vchanges = changes->vectat(i,i+1);
    for(unsigned int j=i+1; j<ql.size; ++j)
      *vchanges++ = (1.0f/log2(i+2.0f)-1.0f/log2(j+2.0f))*(POWEROFTWO(ql.labels[i])-POWEROFTWO(ql.labels[j]));
  }
  return changes;
}
float DCGScorer::get_dcg(unsigned int const* rel, const unsigned int relsize, const unsigned int k) {
  //NOTE is this method still necessary?
  unsigned int size = (k>relsize or k<=0) ? relsize : k;
  float dcg = 0.0f;
  for(unsigned int i=1; i<=size; ++i)
    dcg += (POWEROFTWO(rel[i-1])-1.0f)/log2(i+1.0f);
  return dcg;
}

#undef POWEROFTWO