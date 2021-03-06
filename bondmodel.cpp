#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <array>
#include <string>
#include <fstream>

int L; // System Size
int N; // Number of Sites
double p1 = 0.15;//syokikakuritu

std::vector<int> parent;

void init(int size) {
  L = size;
  N = L * L;
  parent.resize(N);
}

int find(int i) {
  while (i != parent[i]) {
    i = parent[i];
  }
  return i;
}

void unite(int i, int j) {
  i = find(i);
  j = find(j);
  parent[j] = i;
}

void connect(int i, int j, double p, std::mt19937 &mt) {
  std::uniform_real_distribution<> ud(0.0, 1.0);
  if (ud(mt) > p) return;
  unite(i, j);
}

int pos2index(int ix, int iy) {
  ix = (ix + L) % L;
  iy = (iy + L) % L;
  return ix + iy * L;
}

void one_step(double p, std::mt19937 &mt) {
  for (int i = 0; i < N; i++) {
    parent[i] = i;
  }
  for (int iy = 0; iy < L - 1; iy++) {
    for (int ix = 0; ix < L - 1; ix++) {
      int i = pos2index(ix, iy);
      connect(i, pos2index(ix + 1, iy), p, mt); //right
      connect(i, pos2index(ix, iy + 1), p1, mt); //down
    }
  }
}

double crossing_probability(void) {
  for (int ix1 = 0; ix1 < L; ix1++) {
    int i = find(pos2index(ix1, 0));
    int ci = find(i);
    for (int ix2 = 0; ix2 < L; ix2++) {
      int j = find(pos2index(ix2, L - 1));
      int cj = find(j);
      if (ci == cj)
        return 1.0;
    }
  }
  return 0.0;
}

double crossing_probability2(void) {
  for (int ix1 = 0; ix1 < L; ix1++) {
    int i = find(pos2index(0, ix1));
    int ci = find(i);
    for (int ix2 = 0; ix2 < L; ix2++) {
      int j = find(pos2index(L-1, ix2));
      int cj = find(j);
      if (ci == cj)
        return 1.0;
    }
  }
  return 0.0;
}

double percolation_probability(void) {
  std::vector<int> size(N, 0);
  for (int i = 0; i < N; i++) {
    int ci = find(i);
    size[ci]++;
  }
  int max = *std::max_element(size.begin(), size.end());
  return static_cast<double>(max) / N;
}

double mc_cp_y(double p) {
  const int observe_loop = 1000;
  std::mt19937 mt;
  double cp = 0;
  //double pp = 0.0;
  //std::ofstream fp;
  //std::string filename;
  //filename = "percolation.dat";
  //fp.open(filename, std::ios::out);

  for (int i = 0; i < observe_loop; i++) {
    one_step(p, mt);
    cp += crossing_probability();
    //pp += percolation_probability();
  }
  cp /= static_cast<double>(observe_loop);
  //pp /= static_cast<double>(observe_loop);
  //fp << p << "\t" << cp << "\t" << pp << std::endl;
 // std::cout << p << " " << cp << " " << pp << std::endl;
  //fp.close();
  /*FILE* fp
    fp = fopen("percolation.dat" , "w");
    if(fp == NULL){
      printf("File open faild.");
    }
  fprintf(fp, "p\tcp\tpp");
  fclose(fp);*/
  return cp;
}

double mc_cp_x(double p) {
  const int observe_loop = 1000;
  std::mt19937 mt;
  double cp = 0;

  for (int i = 0; i < observe_loop; i++) {
    one_step(p, mt);
    cp += crossing_probability2();
  }
  cp /= static_cast<double>(observe_loop);
  return cp;
}

double mc_pp(double p) {
  const int observe_loop = 1000;
  std::mt19937 mt;
  //double cp = 0;
  double pp = 0.0;
//  std::ofstream fp;
 // std::string filename;
 // filename = "percolation.dat";
 // fp.open(filename, std::ios::out);

  for (int i = 0; i < observe_loop; i++) {
    one_step(p, mt);
    //cp += crossing_probability();
    pp += percolation_probability();
  }
  //cp /= static_cast<double>(observe_loop);
  pp /= static_cast<double>(observe_loop);
  //fp << p << "\t" << cp << "\t" << pp << std::endl;
 // std::cout << p << " " << cp << " " << pp << std::endl;
  //fp.close();
  //FILE* fp
    //fp = fopen("percolation.dat" , "w");
    //if(fp == NULL){
      //printf("File open faild.");
    //}
  //fprintf(fp, "p\tcp\tpp");
  //fclose(fp);
  return pp;
}

int main(void) {
  //int ND = 50;
  int ND =45;
  //int size = 32;
  int size = 40;
  init(size);
  double cp_y, cp_x;
  double pp;

  std::ofstream fp;
  std::string filename;
  filename = "percolation_2cp40.dat";
  fp.open(filename, std::ios::out);
  fp << "f" << "\t" << "cp_y" << "\t" << "cp_x" << std::endl;

  std::ofstream fp1;
  std::string filename1;
  filename1 = "percolation_2pp40.dat";
  fp1.open(filename1, std::ios::out);
  fp1 << "f" << "\t" << "pp" << std::endl;

  for (int i = 0; i <= ND; i++) {
    //double p = static_cast<double>(i) / ND;
    double f = 0.17*static_cast<double>(i);
    double p = - (0.046875)*f*f+0.375*f+0.15;
    //mc(p);
    cp_y = mc_cp_y(p);
    cp_x = mc_cp_x(p);
    fp << f << "\t" << cp_y << "\t" << cp_x << std::endl;

    pp = mc_pp(p);
    fp1 << f << "\t" << pp << std::endl;
  }
  fp.close();
  fp1.close();
}

