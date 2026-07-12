 #define _USE_MATH_DEFINES
  #include <iostream>
  #include <cstdlib>
  #include <ctime>
  #include <cmath>
  #include "mySort_old.h"
  using namespace std;

  long long compareCount = 0;
  long long assignCount = 0;

  //生成随机数 
  double UniformRand(double a, double b)
  {
      return a + rand() * (b - a) / RAND_MAX;
  }

  double GaussRand(double mean, double variance)
  {
      static double u, v;
      static int phase = 0;
      double z;

      if(phase == 0)
      {
          u = (rand() + 1.0) / (RAND_MAX + 1.0);
          v = (rand() + 1.0) / (RAND_MAX + 1.0);
          z = sqrt(-2.0 * log(u)) * sin(2.0 * M_PI * v);
      }
      else
      {
          z = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
      }
      phase = 1 - phase;
      return mean + z * sqrt(variance);
  }

  //计时器 
  double gettime(int restart=0)
  {
      const double c = 1.0 / CLOCKS_PER_SEC;
      static clock_t t = clock();
      if(restart) t = clock();
      return c * (clock() - t);
  }

  //生成测试数据 
  void InitData(int *data, int n, int flag)
  {
      switch(flag)
      {
          case -1: for(int i=0; i<n; i++) data[i] = n-1-i; break;
          case 0:  for(int i=0; i<n; i++) data[i] = i; break;
          case 1:  for(int i=0; i<n; i++) data[i] = (int)UniformRand(54,90); break;
          case 2:  for(int i=0; i<n; i++) data[i] = (int)GaussRand(72, 36); break;
      }
  }

  void CopyArray(int *dest, int *src, int n)
  {
      for(int i=0; i<n; i++) dest[i] = src[i];
  }

  int main()
  {
      srand(time(NULL));

      char dataType[][30] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};
      int sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536};
      int numSizes = 7;

      cout <<  "========== 希尔排序性能测试 ==========" << endl;

      for(int flag = -1; flag <= 2; flag++)
      {
          cout << "\n==========================================" << endl;
          cout << "数据分布: " << dataType[flag+1] << endl;
          cout << "规模\t时间(秒)\t比较次数\t赋值次数" << endl;
          cout << "------------------------------------------" << endl;

          for(int s = 0; s < numSizes; s++)
          {
              int n = sizes[s];
              int *orig = new int[n];
              int *data = new int[n];

              InitData(orig, n, flag);
              CopyArray(data, orig, n);

              compareCount = 0;
              assignCount = 0;
              gettime(1);

              ShellSort(data, n);

              double timeUsed = gettime();
              bool ok = Check(data, n);

              cout << n << "\t" << timeUsed << "\t\t"
                   << compareCount << "\t\t" << assignCount
                   << (ok ? "\t正确" : "\t错误") << endl;

              delete[] orig;
              delete[] data;
          }
      }

      cout << "\n按回车键退出...";
      cin.get();
      return 0;
  }
