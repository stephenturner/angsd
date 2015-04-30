#pragma once
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <map>
#include <htslib/bgzf.h>

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};


typedef struct{
  size_t nSites;
  int64_t pos;
  int64_t saf;
}datum;

typedef std::map<char*,datum,ltstr> myMap;

typedef struct{
  size_t nSites;
  size_t nChr;
  myMap mm;
  BGZF *pos;
  BGZF *saf;
  size_t fsize;//contains an estimate of the uncompressed fsize
  int version;
}persaf;


persaf* readsaf(const char *fname);
void writesaf_header(FILE *fp,persaf *pp);
void destroy(persaf *pp);