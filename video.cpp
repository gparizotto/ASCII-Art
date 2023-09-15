#include <algorithm>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>

using namespace std;
using namespace cv;

string characters = " .-:+!|}upyaO8#@";
int HEIGHT, WIDTH, rows, cols, CellSizeHeight, CellSizeWidth, CellArea;

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

int main() {
  Mat image;
  string path = "image2.jpeg";
  VideoCapture capture;

  if(!capture.open(0)) {
    cout << "Error oppening camera\n";
    return -1;
  }

  rows = getTerminalRows();
  cols = getTerminalColumns();
  while(true) {

    capture >> image; 

    if(image.empty()) {
      cout << "Error capturing frame\n";
      return -1;
    }

    HEIGHT = image.rows;
    WIDTH = image.cols;
    CellSizeHeight = HEIGHT / rows;  
    CellSizeWidth = WIDTH / cols;
    CellArea= CellSizeWidth * CellSizeHeight;


    cvtColor(image, image, COLOR_BGR2GRAY);

    string ans = "", aux = "";

    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
        long long int sum = 0;

        for(int x = i * CellSizeHeight; x < (i + 1) * CellSizeHeight; x++) {
          for(int y = j * CellSizeWidth; y < (j + 1) * CellSizeWidth; y++) {
            sum += image.at<uchar>(x, y);
          }
        }

        double average = static_cast<double>(sum) / CellArea;
        int index = characters.size() * (int)average / 255; 
        aux += characters[index];
        // 255 -- characters.size()
        // avg -- index

      }
      reverse(aux.begin(), aux.end());
      ans += aux + "\n"; 
      aux.clear();
    }

    cout << ans;  
    image.release();
  }
  return 0;
}
