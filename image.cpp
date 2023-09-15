#include <algorithm>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>

using namespace std;
using namespace cv;

int getTerminalColumns() {
  int columns = 0;

  // Abrir o comando "tput cols" em modo de leitura
  FILE* fp = popen("tput cols", "r");
  if (fp != nullptr) {
    // Ler o valor de colunas do comando
    fscanf(fp, "%d", &columns);
    // Fechar a stream
    pclose(fp);
  }

  return columns;
}

int getTerminalRows() {
  int rows = 0;

  // Abrir o comando "tput lines" em modo de leitura
  FILE* fp = popen("tput lines", "r");
  if (fp != nullptr) {
    // Ler o valor de linhas do comando
    fscanf(fp, "%d", &rows);
    // Fechar a stream
    pclose(fp);
  } else {
    cerr << "Erro ao executar o comando tput." << std::endl;
    exit(EXIT_FAILURE);
  }

  return rows;
}

int init(Mat *image, string path) {
  *image = imread(path);

  if((*image).empty()) {
    return -1;
  }

  cvtColor(*image, *image, COLOR_BGR2GRAY);
  return 1;
}

int main() {
  Mat image;
  string path = "image.jpeg";
  string characters = " .-:+!)|}lu[ya8#@";
  characters = " .-=+*padOAP#%@";

  if(init(&image, path) == -1) {
    cout << "Error oppening the image\n";
    return -1;
  }

  int HEIGHT = image.rows;
  int WIDTH = image.cols;
  int BLOCK_SIZE = 2;
  int cols = getTerminalColumns();
  int rows;

  double ScaleFactor = (double)HEIGHT / WIDTH;
  rows = (int)(ScaleFactor * cols);

  cout << HEIGHT << " " <<  WIDTH << '\n';
  cout << rows << " " << cols << '\n';

  int CellSizeWidth = WIDTH / cols;


   cout << rows << " " << cols;

  int CellArea = CellSizeWidth * CellSizeWidth;

  string ans = "";


  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      long long int sum = 0;

      for(int x = i * CellSizeWidth; x < (i + 1) * CellSizeWidth; x++) {
        for(int y = j * CellSizeWidth; y < (j + 1) * CellSizeWidth; y++) {
          sum += image.at<uchar>(x, y);
        }
      }

      double average = static_cast<double>(sum) /CellArea; 
      int index = characters.size() * (int)average / 255; 
      ans += characters[index];
      // 255 -- characters.size()
      // avg -- index
    }
    ans += "\n";
  }
  cout << ans;
  image.release();
  return 0;
}
