#include<fstream>
using namespace std;
int main(){

FILE* file = fopen("ghost.txt" , "r");
 
 if (file==nullptr)
  perror("failed to open file");
  return 0;
}